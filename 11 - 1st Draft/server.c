#include "shared.h"

//int search(char* file_name, int32_t* write_address);
void* search(void* ptr);

int main()
{	
	// Shared Memory Initialization
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);

	int32_t* ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	// Shared memory data segments
	int32_t* orig = ptr;
	int32_t* queue_state = ptr;
	int32_t* result_queue_1 = ptr + RESULT_QUEUE_1_START;
	int32_t* result_queue_2 = ptr + RESULT_QUEUE_2_START;
	int32_t* result_queue_3 = ptr + RESULT_QUEUE_3_START;
	int32_t* result_queue_4 = ptr + RESULT_QUEUE_4_START;
	int32_t* result_queue_5 = ptr + RESULT_QUEUE_5_START;
	int32_t* result_queue_6 = ptr + RESULT_QUEUE_6_START;
	int32_t* result_queue_7 = ptr + RESULT_QUEUE_7_START;
	int32_t* result_queue_8 = ptr + RESULT_QUEUE_8_START;
	int32_t* result_queue_9 = ptr + RESULT_QUEUE_9_START;
	int32_t* result_queue_10 = ptr + RESULT_QUEUE_10_START;
	int32_t* request_1 = ptr + REQUEST_1_START;
	int32_t* request_2 = ptr + REQUEST_2_START;
	int32_t* request_3 = ptr + REQUEST_3_START;
	int32_t* request_4 = ptr + REQUEST_4_START;
	int32_t* request_5 = ptr + REQUEST_5_START;
	int32_t* request_6 = ptr + REQUEST_6_START;
	int32_t* request_7 = ptr + REQUEST_7_START;
	int32_t* request_8 = ptr + REQUEST_8_START;
	int32_t* request_9 = ptr + REQUEST_9_START;
	int32_t* request_10 = ptr + REQUEST_10_START;
	int32_t* isEmpty = ptr + IS_EMPTY_REQUEST;
	int32_t* rq1_element_count = ptr + RQ1_ELEMENT_COUNT_INDEX;
	int32_t* rq1_read_index = ptr + RQ1_READ_INDEX;
	int32_t* rq1_write_index = ptr + RQ1_WRITE_INDEX;
	int32_t* rq2_element_count = ptr + RQ2_ELEMENT_COUNT_INDEX;
	int32_t* rq2_read_index = ptr + RQ2_READ_INDEX;
	int32_t* rq2_write_index = ptr + RQ2_WRITE_INDEX;
	int32_t* rq3_element_count = ptr + RQ3_ELEMENT_COUNT_INDEX;
	int32_t* rq3_read_index = ptr + RQ3_READ_INDEX;
	int32_t* rq3_write_index = ptr + RQ3_WRITE_INDEX;
	int32_t* rq4_element_count = ptr + RQ4_ELEMENT_COUNT_INDEX;
	int32_t* rq4_read_index = ptr + RQ4_READ_INDEX;
	int32_t* rq4_write_index = ptr + RQ4_WRITE_INDEX;
	int32_t* rq5_element_count = ptr + RQ5_ELEMENT_COUNT_INDEX;
	int32_t* rq5_read_index = ptr + RQ5_READ_INDEX;
	int32_t* rq5_write_index = ptr + RQ5_WRITE_INDEX;
	int32_t* rq6_element_count = ptr + RQ6_ELEMENT_COUNT_INDEX;
	int32_t* rq6_read_index = ptr + RQ6_READ_INDEX;
	int32_t* rq6_write_index = ptr + RQ6_WRITE_INDEX;
	int32_t* rq7_element_count = ptr + RQ7_ELEMENT_COUNT_INDEX;
	int32_t* rq7_read_index = ptr + RQ7_READ_INDEX;
	int32_t* rq7_write_index = ptr + RQ7_WRITE_INDEX;
	int32_t* rq8_element_count = ptr + RQ8_ELEMENT_COUNT_INDEX;
	int32_t* rq8_read_index = ptr + RQ8_READ_INDEX;
	int32_t* rq8_write_index = ptr + RQ8_WRITE_INDEX;
	int32_t* rq9_element_count = ptr + RQ9_ELEMENT_COUNT_INDEX;
	int32_t* rq9_read_index = ptr + RQ9_READ_INDEX;
	int32_t* rq9_write_index = ptr + RQ9_WRITE_INDEX;
	int32_t* rq10_element_count = ptr + RQ10_ELEMENT_COUNT_INDEX;
	int32_t* rq10_read_index = ptr + RQ10_READ_INDEX;
	int32_t* rq10_write_index = ptr + RQ10_WRITE_INDEX;
	int32_t* signal_client_1 = ptr + SIGNAL_1;
	int32_t* signal_client_2 = ptr + SIGNAL_2;
	int32_t* signal_client_3 = ptr + SIGNAL_3;
	int32_t* signal_client_4 = ptr + SIGNAL_4;
	int32_t* signal_client_5 = ptr + SIGNAL_5;
	int32_t* signal_client_6 = ptr + SIGNAL_6;
	int32_t* signal_client_7 = ptr + SIGNAL_7;
	int32_t* signal_client_8 = ptr + SIGNAL_8;
	int32_t* signal_client_9 = ptr + SIGNAL_9;
	int32_t* signal_client_10 = ptr + SIGNAL_10;

	pthread_t pthread_array[10];
	for(int i = 0; i < N; i++)
		pthread_array[i] =-1;

	// Queue State Initialization
	for(int i = 0; i < N; i++) {
		ptr[i] = 0;
	}

	// Queue State Semaphore Initialization
	if((semaphore_queue_state = sem_open(SEMQS, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMQS\n");
			exit(1);
		}
		sem_unlink(SEMQS);
	}

	if((client_thread_1 = sem_open(SEMCT1, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT1\n");
			exit(1);
		}
		sem_unlink(SEMCT1);
	}

	if((client_thread_2 = sem_open(SEMCT2, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT2\n");
			exit(1);
		}
		sem_unlink(SEMCT2);
	}

	if((client_thread_3 = sem_open(SEMCT3, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT3\n");
			exit(1);
		}
		sem_unlink(SEMCT3);
	}

	if((client_thread_4 = sem_open(SEMCT4, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT4\n");
			exit(1);
		}
		sem_unlink(SEMCT4);
	}

	if((client_thread_5 = sem_open(SEMCT5, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT5\n");
			exit(1);
		}
		sem_unlink(SEMCT5);
	}

	if((client_thread_6 = sem_open(SEMCT6, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT6\n");
			exit(1);
		}
		sem_unlink(SEMCT6);
	}

	if((client_thread_7 = sem_open(SEMCT7, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT7\n");
			exit(1);
		}
		sem_unlink(SEMCT7);
	}

	if((client_thread_8 = sem_open(SEMCT8, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT8\n");
			exit(1);
		}
		sem_unlink(SEMCT8);
	}

	if((client_thread_9 = sem_open(SEMCT9, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT9\n");
			exit(1);
		}
		sem_unlink(SEMCT9);
	}

	if((client_thread_10 = sem_open(SEMCT10, O_CREAT | O_EXCL, SEM_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEMCT10\n");
			exit(1);
		}
		sem_unlink(SEMCT10);
		exit(0);
	}

	printf("Reading results...\n");
	fflush(stdout);
	getchar(); // !!!

	for(int32_t i = 0; i < N; i++) {
		if(ptr[i] == 1) {
			int32_t* rptr;
			int32_t* element_count;
			int32_t* read_index;
			int32_t* write_index;
			sem_t* semaphore;
			int32_t* signal_client;
			switch(i) {
				case 0 :
					rptr = request_1;
					element_count = rq1_element_count;
					read_index = rq1_read_index;
					write_index = rq1_write_index;
					semaphore = client_thread_1;
					signal_client = signal_client_1;
					break;
					
				case 1 :
					rptr = request_2;
					element_count = rq2_element_count;
					read_index = rq2_read_index;
					write_index = rq2_write_index;
					semaphore = client_thread_2;
					signal_client = signal_client_2;
					break;
				
				case 2 :
					rptr = request_3;
					element_count = rq3_element_count;
					read_index = rq3_read_index;
					write_index = rq3_write_index;
					semaphore = client_thread_3;
					signal_client = signal_client_3;
					break;

				case 3 :
					rptr = request_4;
					element_count = rq4_element_count;
					read_index = rq4_read_index;
					write_index = rq4_write_index;
					semaphore = client_thread_4;
					signal_client = signal_client_4;
					break;

				case 4 :
					rptr = request_5;
					element_count = rq5_element_count;
					read_index = rq5_read_index;
					write_index = rq5_write_index;
					semaphore = client_thread_5;
					signal_client = signal_client_5;
					break;

				case 5 :
					rptr = request_6;
					element_count = rq6_element_count;
					read_index = rq6_read_index;
					write_index = rq6_write_index;
					semaphore = client_thread_6;
					signal_client = signal_client_6;
					break;

				case 6 :
					rptr = request_7;
					element_count = rq7_element_count;
					read_index = rq7_read_index;
					write_index = rq7_write_index;
					semaphore = client_thread_7;
					signal_client = signal_client_7;
					break;

				case 7 :
					rptr = request_8;
					element_count = rq8_element_count;
					read_index = rq8_read_index;
					write_index = rq8_write_index;
					semaphore = client_thread_8;
					signal_client = signal_client_8;
					break;

				case 8 :
					rptr = request_9;
					element_count = rq9_element_count;
					read_index = rq9_read_index;
					write_index = rq9_write_index;
					semaphore = client_thread_9;
					signal_client = signal_client_9;
					break;

				case 9 :
					rptr = request_10;
					element_count = rq10_element_count;
					read_index = rq10_read_index;
					write_index = rq10_write_index;
					semaphore = client_thread_10;
					signal_client = signal_client_10;
					break;
					
				default :
					printf("Error: unknown request index\n");
					rptr = NULL;
					element_count = NULL;
					read_index = NULL;
					write_index = NULL;
					semaphore = NULL;
					break;
			}

			if(rptr == NULL) {
				printf("Server exiting with rptr = NULL\n");
				break;
			}
			else {
				// Print Request
				char s[129];
				
				for(int32_t i = 1; i < 128; i++) {
					if(rptr[i] != '\0')
						s[i-1] = rptr[i];
					else {
						s[i-1] = '\0';
						break;
					}
				}
					
				printf("SERVER: Read successful at request %d; result queue index: %d; keyword: %s\n", i, rptr[0], s);

				// Process Request
				// Version 1: write to a fixed-sized, large-enough buffer
				pthread_t thread;
				pthread_attr_t attr;
				int32_t* search_arguments[7] = {0};

				*element_count = 0;
				*read_index = 0;
				*write_index = 0;
				*signal_client = 0;

				search_arguments[0] = element_count;
				search_arguments[1] = read_index;
				search_arguments[2] = write_index;
				search_arguments[3] = (int32_t*)s;
				search_arguments[4] = (int32_t*)semaphore;
				search_arguments[5] = orig;
				search_arguments[6] = signal_client;

				int create;
				pthread_attr_init(&attr);
				pthread_attr_setstacksize(&attr, 8192);
				if((create = pthread_create(&thread, &attr, search, (void*)search_arguments) < 0)) {
					fprintf(stderr, "SERVER: Cannot create thread\n");
				}
				printf("SERVER: Thread created\n");
				pthread_array[i] = thread;
			}
		}
	}

	/*printf("Removing semaphores...\n");
	getchar();
	getchar();
	fflush(stdout);*/

	printf("Waiting for threads to finish...\n");
	for(int i = 0; i < 10; i++) {
		if(pthread_array[i] != -1)
			pthread_join(pthread_array[i], NULL);
	}

	// Exit Code
	// Unlink SEM01
	printf("Exitting...\n");
	int32_t sdestroy = sem_unlink(SEMQS);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEM01\n");
	}

	sdestroy = sem_unlink(SEMCT1);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT1\n");
	}

	sdestroy = sem_unlink(SEMCT2);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT2\n");
	}

	sdestroy = sem_unlink(SEMCT3);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT13\n");
	}

	sdestroy = sem_unlink(SEMCT4);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT4\n");
	}

	sdestroy = sem_unlink(SEMCT5);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT5\n");
	}

	sdestroy = sem_unlink(SEMCT6);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT6\n");
	}

	sdestroy = sem_unlink(SEMCT7);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT7\n");
	}

	sdestroy = sem_unlink(SEMCT8);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT8\n");
	}

	sdestroy = sem_unlink(SEMCT9);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT9\n");
	}

	sdestroy = sem_unlink(SEMCT10);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEMCT10\n");
	}

	printf("Server exiting...\n");
	exit(0);
}

/*int search(char* file_name, int32_t* write_address) {
    char buffer[1100];
    size_t nread;

    int lineNo = 1, index = 0;

    FILE *file = fopen("test.txt", "r");
    if (file) {
        while ((nread = fread(buffer, 1, 1024, file)) > 0) {
            if(strstr(buffer, file_name)) {
                write_address[index] = lineNo;
                index++;
            }
            lineNo++;
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Cannot open input file test.txt\n");
        return 1;
    }
	return 0;
}*/

void* search(void* ptr){
	int32_t** search_arguments = (int32_t**)ptr;
	int32_t* element_count = search_arguments[0];
	int32_t* read_index = search_arguments[1];
	int32_t* write_index = search_arguments[2];
	char* keyword = (char*)(search_arguments[3]);
	sem_t* semaphore = (sem_t*)(search_arguments[4]);
	int32_t* shm = search_arguments[5];
	int32_t* signal_client = search_arguments[6];

	// Do the searching
	int32_t data[129] = {0};

	char buffer[1100];
    size_t nread;

    int lineNo = 1, index = 0;

    FILE *file = fopen("test.txt", "r");
    if (file) {
        while ((nread = fread(buffer, 1, 1024, file)) > 0) {
            if(strstr(buffer, keyword)) {
                data[index] = lineNo;
                index++;
            }
            lineNo++;
        }
        fclose(file);
    }

	// Sync-write to client's buffer
	int i = 0;
	int times = 0;
	*signal_client = 0;
	while(data[i] != 0 || times < 128) {
		sem_wait(semaphore);
		if(*element_count < 10) {
			shm[*write_index] = data[i];
			*write_index = (*write_index + 1) % 10;
			*element_count = *element_count + 1;
			i++;
			times++;
		}
		sem_post(semaphore);
		sleep(1);
	}
	
	shm[*write_index] = -1;
	pthread_exit(0);
}