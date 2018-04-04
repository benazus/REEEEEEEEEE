#include "shared.h"

//int search(char* file_name, int32_t* write_address);
void* search(void* ptr);

char file_name[128];

int main(int argc, char** argv) {
    char shm_name[128];
    char sem_name [128];

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
            file_name[i] = argv[2][i];
            count2++;
        }
        else break;
    }

    for(int i = 0; i < 128; i++) {    
        if(argv[3][i] != '\0') {
            sem_name[i] = argv[3][i];
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
        file_name[count2] = '\0';
    }
    else
        file_name[127] = '\0';

    if(count3 < 128) {
        sem_name[count3] = '\0';
    }
    else
        sem_name[127] = '\0';

    if(strlen(file_name) >= MAX_FILENAME || strlen(sem_name) >= MAX_SEMNAME || strlen(shm_name) >= MAX_SHMNAME) {
        printf("Invalid arguments\n");
        exit(1);
    }

    printf("file_name: %s, sem_name: %s, shm_name: %s\n", file_name, sem_name, shm_name);

    int shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if(shm_fd == -1) {
        if(errno != EEXIST) {
            fprintf(stderr, "Error in shm_open\n");
            exit(1);
        }
    }
    ftruncate(shm_fd, sizeof(struct shared_memory_segment));    

    // Semaphore Queue State
    char semaphore_queue_state_name[140];
    for(int i = 0; i < 128; i++)
        semaphore_queue_state_name[i] = sem_name[i];
    strcat(semaphore_queue_state_name, "_queue_state");

    for(int i = 0; i < strlen(semaphore_queue_state_name) + 1; i++)
        printf("%c", semaphore_queue_state_name[i]);
    printf("\n");


    char semaphore_1_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_1_name[i] = sem_name[i];
    strcat(semaphore_1_name, "_1");

    char semaphore_2_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_2_name[i] = sem_name[i];
    strcat(semaphore_2_name, "_2");

    char semaphore_3_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_3_name[i] = sem_name[i];
    strcat(semaphore_3_name, "_3");

    char semaphore_4_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_4_name[i] = sem_name[i];
    strcat(semaphore_4_name, "_4");

    char semaphore_5_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_5_name[i] = sem_name[i];
    strcat(semaphore_5_name, "_5");

    char semaphore_6_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_6_name[i] = sem_name[i];
    strcat(semaphore_6_name, "_6");

    char semaphore_7_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_7_name[i] = sem_name[i];
    strcat(semaphore_7_name, "_7");

    char semaphore_8_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_8_name[i] = sem_name[i];
    strcat(semaphore_8_name, "_8");

    char semaphore_9_name[130];
    for(int i = 0; i < 128; i++)
        semaphore_9_name[i] = sem_name[i];
    strcat(semaphore_9_name, "_9");

    char semaphore_10_name[131];
    for(int i = 0; i < 128; i++)
        semaphore_10_name[i] = sem_name[i];
    strcat(semaphore_10_name, "_10");

    sem_t* semaphore_queue_state = sem_open(semaphore_queue_state_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
    // sem_t* semaphore_queue_state = sem_open(semaphore_queue_state_name, O_CREAT, 0666, 1);
    if(semaphore_queue_state == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_queue_state\n");
		    
		} else {
            fprintf(stderr, "Cannot open semaphore_queue_state\n");
        }
        //fprintf(stderr, "Error in semaphore_queue_state\n");
	}

    sem_t* semaphore_1 = sem_open(semaphore_1_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_1 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_1\n");
            
		} else {
            fprintf(stderr, "Cannot open semaphore_1\n");
        }
        //fprintf(stderr, "Error in semaphore_1\n");
	}

    sem_t* semaphore_2 = sem_open(semaphore_2_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_2 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_2\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_2\n");
        }
        //fprintf(stderr, "Error in semaphore_2\n");
	}

    sem_t* semaphore_3 = sem_open(semaphore_3_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_3 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_3\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_3\n");
        }
        //fprintf(stderr, "Error in semaphore_3\n");
	}

    sem_t* semaphore_4 = sem_open(semaphore_4_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_4 == SEM_FAILED) {
		if(errno == EEXIST) {		
            printf("EEXIST: Unlinking semaphore_4\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_4\n");
        }
        //fprintf(stderr, "Error in semaphore_4\n");
	}

    sem_t* semaphore_5 = sem_open(semaphore_5_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_5 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_5\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_5\n");
        }
        //fprintf(stderr, "Error in semaphore_5\n");
	}

    sem_t* semaphore_6 = sem_open(semaphore_6_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_6 == SEM_FAILED) {
		if(errno == EEXIST) {			
            printf("EEXIST: Unlinking semaphore_6\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_6\n");
        }
        //fprintf(stderr, "Error in semaphore_6\n");
	}

    sem_t* semaphore_7 = sem_open(semaphore_7_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_7 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_7\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_7\n");
        }
        //fprintf(stderr, "Error in semaphore_7\n");
	}

    sem_t* semaphore_8 = sem_open(semaphore_8_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_8 == SEM_FAILED) {
		if(errno == EEXIST) {		
            printf("EEXIST: Unlinking semaphore_8\n");
		} else {
            fprintf(stderr, "Cannot open semaphore_8\n");
        }
        //fprintf(stderr, "Error in semaphore_8\n");
	}

    sem_t* semaphore_9 = sem_open(semaphore_9_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_9 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_9\n");			
		} else {
            fprintf(stderr, "Cannot open semaphore_9\n");
        }
        //fprintf(stderr, "Error in semaphore_9\n");
	}

    sem_t* semaphore_10 = sem_open(semaphore_10_name, O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH, 1);
	if(semaphore_10 == SEM_FAILED) {
		if(errno == EEXIST) {
            printf("EEXIST: Unlinking semaphore_10\n"); 
		} else {
			fprintf(stderr, "Cannot open semaphore_10\n");
        }
        //fprintf(stderr, "Error in semaphore_10\n");
	}

    void* ptr = mmap(0, sizeof(struct shared_memory_segment), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
    }
    
    /*shm_unlink(shm_name);
    sem_unlink(semaphore_queue_state_name);
    sem_unlink(semaphore_1_name);
    sem_unlink(semaphore_2_name);
    sem_unlink(semaphore_3_name);
    sem_unlink(semaphore_4_name);
    sem_unlink(semaphore_5_name);
    sem_unlink(semaphore_6_name);
    sem_unlink(semaphore_7_name);
    sem_unlink(semaphore_8_name);
    sem_unlink(semaphore_9_name);
    sem_unlink(semaphore_10_name);
    exit(1);*/

    shared_memory_segment* shared_memory = (shared_memory_segment*)ptr;
    for(int i = 0; i < N; i++) {
        shared_memory->search_queue_state[i] = 0;
    }

    shared_memory->search_request_queue.in = 0;
    shared_memory->search_request_queue.out = 0;
    for(int i = 0; i < N; i++) {
        shared_memory->search_result_queue[i].in = 0;
        shared_memory->search_result_queue[i].out = 0;
    }

    while(1){
        while(shared_memory->search_request_queue.out == shared_memory->search_request_queue.in)
            sleep(0.25);

        search_arguments* sargs = (search_arguments*)malloc(sizeof(search_arguments));
        
        sargs->keyword = shared_memory->search_request_queue
            .requests[shared_memory->search_request_queue.out].keyword;
        
        sargs->index = shared_memory->search_request_queue
            .requests[shared_memory->search_request_queue.out].index;
        
        shared_memory->search_request_queue.out = (shared_memory->search_request_queue.out + 1) % (N + 1);
        
        printf("keyword: %s; index: %d\n", sargs->keyword, sargs->index);
        sem_t* semaphore;
        switch(sargs->index) {
            case 0:
                semaphore = semaphore_1;
                break;
            case 1:
                semaphore = semaphore_2;
                break;
            case 2:
                semaphore = semaphore_3;
                break;
            case 3:
                semaphore = semaphore_4;
                break;
            case 4:
                semaphore = semaphore_5;
                break;
            case 5:
                semaphore = semaphore_6;
                break;
            case 6:
                semaphore = semaphore_7;
                break;
            case 7:
                semaphore = semaphore_8;
                break;
            case 8:
                semaphore = semaphore_9;
                break;
            case 9:
                semaphore = semaphore_10;
                break;
            default:
                printf("Error: Invalid index");
                break;
        }
        sargs->semaphore = semaphore;
        sargs->shared_memory = shared_memory;

        pthread_t thread;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&thread, &attr, search, (void*)sargs);
    }
}

void *search(void* ptr){
    search_arguments* args = (search_arguments*)ptr;
    char* keyword = args->keyword;
    int32_t index = args->index;
    shared_memory_segment* shm = args->shared_memory;
    sem_t* semaphore = args->semaphore;
    char buffer[1025];
    size_t nread;
    int line = MIN_LINENO;
    FILE* file = fopen(file_name, "r");
    if(file) {
        while(fgets(buffer, MAX_LINE, file)) {
            if(strstr(buffer, keyword)) {
                while((shm->search_result_queue[index].in + 1) % (BUFFER_SIZE) == shm->search_result_queue[index].out);
                sem_wait(semaphore);
                shm->search_result_queue[index].data[shm->search_result_queue[index].in] = line;
                printf("index = %d, data = %d\n", shm->search_result_queue[index].in, shm->search_result_queue[index].data[shm->search_result_queue[index].in]);
                fflush(stdout);
                shm->search_result_queue[index].in = (shm->search_result_queue[index].in + 1) % BUFFER_SIZE;
                sem_post(semaphore);
            }
            line++;
            sleep(0.25);
        }
    }
    
    sem_wait(semaphore);
    shm->search_result_queue[index].data[shm->search_result_queue[index].in] = -1;
    shm->search_result_queue[index].in = (shm->search_result_queue[index].in + 1) % BUFFER_SIZE;
    sem_post(semaphore);

    free(args);
    printf("Request processed, thread exiting...\n");
    fflush(stdout);
    pthread_exit(NULL);
}