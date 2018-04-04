#include "shared.h"

// http://manpages.ubuntu.com/manpages/xenial/man1/gdb.1.html

int main(int argc, char **argv) {
    char shm_name[128];
    char keyword[128];
    char semaphore_name[128];
    
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    for(int i = 0; i < 128; i++) {
        if(argv[1][i] != '\0') {
            shm_name[i] = argv[1][i];
            count1++;
        }
        else break;
    }

    for(int i = 0; i < 128; i++) {
        if(argv[2][i] != '\0') {
            keyword[i] = argv[2][i];
            count2++;
        }
        else break;
    }

    for(int i = 0; i < 128; i++) {    
        if(argv[3][i] != '\0') {
            semaphore_name[i] = argv[3][i];
            count3++;
        }
        else break;
    }       

    if(count1 < 128) {
        shm_name[count1] = '\0';
    }
    else
        shm_name[127] = '\0';

    if(count2 < 128) {
        keyword[count2] = '\0';
    }
    else
        keyword[127] = '\0';

    if(count3 < 128) {
        semaphore_name[count3] = '\0';
    }
    else
        semaphore_name[127] = '\0';

    if (MAX_SHMNAME <= strlen(shm_name))
    {
        printf("shared memory name length is greater than expected");
        exit(-1);
    }

    if(MAX_KEYWORD <= strlen(keyword) )
    {
        printf("Keyword length is greater than expected");
        exit(-1);
    }

    if (MAX_SEMNAME <= strlen(semaphore_name))
    {
        printf("shared memory name is greater than expected");
        exit(-1);
    }

    char qss[140];
    // strncopy(qss, semaphore_name, strlen(semaphore_name) + 1);
    for(int i = 0; i < strlen(semaphore_name) + 1; i++)
        qss[i] = semaphore_name[i];
    strcat(qss, "_queue_state");

    sem_t* semaphore_queue_state = sem_open(qss, 0);
    if(semaphore_queue_state == SEM_FAILED) {
        fprintf(stderr, "sem_open(semaphore_queue_state) failed\n");
        printf("errno: %u", errno);
        exit(1);
    }

    

    // Open Shared Memory
    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    void* ptr = mmap(0, sizeof(struct shared_memory_segment), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }

    struct shared_memory_segment *sgmnt_ptr = (shared_memory_segment* )ptr;
    //------------Grab Sem----------------------
    
    sem_wait(semaphore_queue_state);
    //----------critial segment start-----------
    bool search = true;
    bool should_exit = false;
    int32_t index = 0;
    while(search)
    {
        if(index >= N)
        {
            search = false;
        }
        else if(sgmnt_ptr->search_queue_state[index]!= 1)
        {
            sgmnt_ptr->search_queue_state[index]= 1;
            search = false;
            should_exit = true;
        }
        else
        {
            index++;
        }
    }
    
    if(should_exit)
    {
        struct search_request s_req;
        //s_req.index = index;
        for(int i = 0; i < strlen(keyword); i++)
        {
            s_req.keyword[i] = keyword[i];
        }
        s_req.keyword[strlen(keyword)] = '\0'; //adding EOF
        s_req.index = index;

        printf("keyword: %s; index: %d\n", s_req.keyword, s_req.index);
        fflush(stdout);

        //adding request to queue
        sgmnt_ptr->search_request_queue.requests[sgmnt_ptr->search_request_queue.in] = s_req;
        if((sgmnt_ptr->search_request_queue.in + 1) % (N + 1) != sgmnt_ptr->search_request_queue.out)
            sgmnt_ptr->search_request_queue.in = (sgmnt_ptr->search_request_queue.in + 1)%(N+1);


        //-----------critical segment end------------
        //-------------Release Sem-------------------
        sem_post(semaphore_queue_state);

        //---------Reading from result_queue---------
        int read = 0;
        char read_sem_name[131];
        // strncopy(read_sem_name, semaphore_name, strlen(semaphore_name) + 1);
        for(int i = 0; i < strlen(semaphore_name) + 1; i++)
            read_sem_name[i] = semaphore_name[i];
        
        char a[4];
        sprintf(a, "_%d", index+1);
        strcat(read_sem_name, a);
        printf("%s\n", read_sem_name);

        sem_t * read_sem = sem_open(read_sem_name, 0);

        while(sgmnt_ptr->search_result_queue[index].data[sgmnt_ptr->search_result_queue[index].out] != -1 && sgmnt_ptr->search_result_queue[index].out != sgmnt_ptr->search_result_queue[index].in)
        {
            //---------Grab Sem----------------------
            sem_wait(read_sem);
            //---------critical segment start--------

            printf("PID = %d picked up read_sem\n", getpid());
            fflush(stdout);
            if(sgmnt_ptr->search_result_queue[index].out!=sgmnt_ptr->search_result_queue[index].in)
            {
                read = sgmnt_ptr->search_result_queue[index].data[sgmnt_ptr->search_result_queue[index].out];
                printf("%d \n", read);

                sgmnt_ptr->search_result_queue[index].out = (sgmnt_ptr->search_result_queue[index].out + 1) % (BUFFER_SIZE);
            }

            //---------critical segment end----------
            //-------------Release Sem---------------
            sem_post(read_sem);

            printf("PID = %d read val = %d at index = %d\n", sgmnt_ptr->search_result_queue[index].data[sgmnt_ptr->search_result_queue[index].out], sgmnt_ptr->search_result_queue[index].out, getpid());
            fflush(stdout);
            printf("PID = %d dropped read_sem\n", getpid());
            fflush(stdout);
            fflush(stdout);
            sleep(0.25);
        }
    }
    else {
        printf("PID = %d terminated because no available result queue exists.\n", getpid());
        sgmnt_ptr->search_queue_state[index] = 0;
        sem_post(semaphore_queue_state);
        exit(0);
    }

    //------------Grab Sem----------------------
    sem_wait(semaphore_queue_state);
    printf("PID = %d picked up semaphore_queue_state\n", getpid());
    fflush(stdout);
    //----------critial segment start------------
    sgmnt_ptr->search_queue_state[index] = 0;
    sgmnt_ptr->search_result_queue[index].out = 0;
    sgmnt_ptr->search_result_queue[index].in = 0;
    sgmnt_ptr->search_result_queue[index].data[sgmnt_ptr->search_result_queue[index].out] = 0;
    //-----------critical segment end------------
    //-------------Release Sem-------------------
    sem_post(semaphore_queue_state);

    printf("PID = %d dropped semaphore_queue_state\n", getpid());
    fflush(stdout);
    //shm_unlink(shm_name);
    exit(0);
}