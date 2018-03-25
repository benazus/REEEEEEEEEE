#include "shared.h"

//int search(char* file_name, int32_t* write_address);
void* search(void* ptr);

char* file_name;

int main(int argc, char** argv) {
    char* shm_name = argv[1];
    file_name = argv[2];
    char* sem_name = argv[3];

    if(strlen(file_name) >= MAX_FILENAME || strlen(sem_name) >= MAX_SEMNAME) {
           printf("Invalid arguments\n");
           exit(1);
       }

    int shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if(shm_fd == -1) {
        if(errno != EEXIST) {
            fprintf(stderr, "Error in shm_open\n");
            exit(1);
        }
        shm_unlink(shm_name);
    }
    ftruncate(shm_fd, sizeof(struct shared_memory_segment));    

    // Semaphore Queue State
    char* semaphore_queue_state_name = sem_name;
    sprintf(semaphore_queue_state_name, "%s", "_queue_state");

    char* semaphore_1_name = sem_name;
    sprintf(semaphore_1_name, "%s", "_1");

    char* semaphore_2_name = sem_name;
    sprintf(semaphore_2_name, "%s", "_2");

    char* semaphore_3_name = sem_name;
    sprintf(semaphore_3_name, "%s", "_3");

    char* semaphore_4_name = sem_name;
    sprintf(semaphore_4_name, "%s", "_4");

    char* semaphore_5_name = sem_name;
    sprintf(semaphore_5_name, "%s", "_5");

    char* semaphore_6_name = sem_name;
    sprintf(semaphore_6_name, "%s", "_6");

    char* semaphore_7_name = sem_name;
    sprintf(semaphore_7_name, "%s", "_7");

    char* semaphore_8_name = sem_name;
    sprintf(semaphore_8_name, "%s", "_8");

    char* semaphore_9_name = sem_name;
    sprintf(semaphore_9_name, "%s", "_9");

    char* semaphore_10_name = sem_name;
    sprintf(semaphore_10_name, "%s", "_10");

    sem_t* semaphore_queue_state = sem_open(semaphore_queue_state_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
    if(semaphore_queue_state == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_queue_state\n");
			exit(1);
		}
		sem_unlink(semaphore_queue_state_name);
	}

    sem_t* semaphore_1 = sem_open(semaphore_1_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_1 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_1\n");
			exit(1);
		}
		sem_unlink(semaphore_1_name);
	}

    sem_t* semaphore_2 = sem_open(semaphore_2_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_2 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_2\n");
			exit(1);
		}
		sem_unlink(semaphore_2_name);
	}

    sem_t* semaphore_3 = sem_open(semaphore_3_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_3 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_3\n");
			exit(1);
		}
		sem_unlink(semaphore_3_name);
	}

    sem_t* semaphore_4 = sem_open(semaphore_4_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_4 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_4\n");
			exit(1);
		}
		sem_unlink(semaphore_4_name);
	}

    sem_t* semaphore_5 = sem_open(semaphore_5_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_5 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_5\n");
			exit(1);
		}
		sem_unlink(semaphore_5_name);
	}

    sem_t* semaphore_6 = sem_open(semaphore_6_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_6 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_6\n");
			exit(1);
		}
		sem_unlink(semaphore_6_name);
	}

    sem_t* semaphore_7 = sem_open(semaphore_7_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_7 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_7\n");
			exit(1);
		}
		sem_unlink(semaphore_7_name);
	}

    sem_t* semaphore_8 = sem_open(semaphore_8_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_8 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_8\n");
			exit(1);
		}
		sem_unlink(semaphore_8_name);
	}

    sem_t* semaphore_9 = sem_open(semaphore_9_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_9 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_9\n");
			exit(1);
		}
		sem_unlink(semaphore_9_name);
	}

    sem_t* semaphore_10 = sem_open(semaphore_10_name, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1);
	if(semaphore_10 == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open semaphore_10\n");
			exit(1);
		}
		sem_unlink(semaphore_10_name);
	}

    void* ptr = mmap(0, sizeof(struct shared_memory_segment), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(1);
    }

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
        while(shared_memory->search_request_queue.out == shared_memory->search_request_queue.in);

        search_arguments sargs;
        
        sargs.keyword = shared_memory->search_request_queue
            .requests[shared_memory->search_request_queue.out].keyword;
        
        sargs.index = shared_memory->search_request_queue
            .requests[shared_memory->search_request_queue.out].index;
        
        shared_memory->search_request_queue.out = (shared_memory->search_request_queue.out + 1) % (N + 1);
        
        sem_t* semaphore;
        switch(sargs.index) {
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
        sargs.semaphore = semaphore;
        sargs.shared_memory = shared_memory;

        pthread_t thread;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&thread, &attr, search, (void*)&sargs);
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
        while((nread = fread(buffer, 1, MAX_LINE, file)) > 0) {
            if(strstr(buffer, keyword)) {
                while((shm->search_result_queue[index].in + 1) % (N + 1) != shm->search_result_queue[index].out);
                sem_wait(semaphore);
                shm->search_result_queue[index].data[shm->search_result_queue[index].in] = line;
                shm->search_result_queue[index].in = (shm->search_result_queue[index].in + 1) % BUFFER_SIZE;
                sem_post(semaphore);
            }
            line++;
            sleep(0.2);
        }
    }

    shm->search_result_queue[index].data[shm->search_result_queue[index].in] = -1;
    pthread_exit(0);
}