#include "shared.h"


int main(int argc, char **argv) {
    const char *shm_name = argv[1];
    const char *keyword = argv[2];
    char *semaphore_name = argv[3];

    if (MAX_SEMNAME < strlen(shm_name))
    {
        printf("shared memory name length is greater than expected");
        exit(-1);
    }

    if(MAX_KEYWORD < strlen(keyword) )
    {
        printf("Keyword length is greater than expected");
        exit(-1);
    }

    if (MAX_SEMNAME < strlen(semaphore_name))
    {
        printf("shared memory name is greater than expected");
        exit(-1);
    }
    /*printf("keyword %s \n", keyword);
    printf("semaphore_name %s \n", semaphore_name);*/

    // Open Shared Memory
    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    void* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }

    struct shared_memory_segment *sgmnt_ptr = (shared_memory_segment* )ptr;

    char * qss = semaphore_name;
    sprintf(qss, "_queue_state");

    //------------Grab Sem----------------------
    sem_t * semaphore_queue_state = sem_open(qss, 0);

    sem_wait(semaphore_queue_state);
    //----------critial segment start-----------
    bool search = true;
    bool exit = false;
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
            exit = true;
        }
        else
        {
            index++;
        }
    }

    if(!exit)
    {
        struct search_request s_req;
        //s_req.index = index;

        for(int i = 0; i < strlen(keyword); i++)
        {
            s_req.keyword[i] = keyword[i];
        }
        s_req.keyword[strlen(keyword)] = '\0';//adding EOF

        printf("keyword from rq: %s", s_req.keyword);

        //adding request to queue
        sgmnt_ptr->search_request_queue.requests[sgmnt_ptr->search_request_queue.in] = s_req;
        if((sgmnt_ptr->search_request_queue.in + 1) % (N + 1) != sgmnt_ptr->search_request_queue.out)
            sgmnt_ptr->search_request_queue.in = (sgmnt_ptr->search_request_queue.in + 1)%(N+1);

        //-----------critical segment end------------
        //-------------Release Sem-------------------
        sem_post(semaphore_queue_state);

        //---------Reading from result_queue---------
        int read = 0;
        char * read_sem_name = semaphore_name;
        sprintf(read_sem_name, "_%d", index);

        sem_t * read_sem = sem_open(read_sem_name,0);

        while(read != -1)
        {
            //---------Grab Sem----------------------
            sem_wait(read_sem);
            //---------critical segment start--------
            if(sgmnt_ptr->search_result_queue[index].out!=sgmnt_ptr->search_result_queue[index].in)
            {
                read = sgmnt_ptr->search_result_queue[index].data[sgmnt_ptr->search_result_queue[index].out];
                printf("%d \n", read);

                sgmnt_ptr->search_result_queue[index].out = (sgmnt_ptr->search_result_queue[index].out + 1) % (BUFFER_SIZE);
            }

            //---------critical segment end----------
            //-------------Release Sem---------------
            sem_post(read_sem);
        }

        //------------Grab Sem----------------------
        sem_wait(semaphore_queue_state);
        //----------critial segment start------------
        sgmnt_ptr->search_queue_state[index] = 0;
        //-----------critical segment end------------
        //-------------Release Sem-------------------
        sem_post(semaphore_queue_state);

        sleep(1);

    }

    //free memory
    shm_unlink(shm_name);


    return 0;
}