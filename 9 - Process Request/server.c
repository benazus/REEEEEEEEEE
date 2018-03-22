#include "shared.h"

int search(char* file_name, int32_t* write_address);
void* initialize_search(void* ptr);

char* search_keyword;

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

	// Queue State Initialization
	for(int i = 0; i < N; i++) {
		*ptr = 0;
		ptr++;
	}

	// Queue State Semaphore Initialization
	if((semaphore_queue_state = sem_open(SEM01, O_CREAT | O_EXCL, SEM01_PERMISSIONS, 1)) == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEM01\n");
			exit(1);
		}
		else {
			fprintf(stderr, "SEM01 already exists.\n");
		}
	}

	printf("Reading results...\n");
	fflush(stdout);
	getchar(); // !!!

	ptr = orig;
	for(int32_t i = 0; i < N; i++) {
		if(ptr[i] == 1) {
			int32_t* rptr;
			switch(i) {
				case 0 :
					rptr = request_1;
					break;
					
				case 1 :
					rptr = request_2;
					break;
				
				case 2 :
					rptr = request_3;
					break;

				case 3 :
					rptr = request_4;
					break;

				case 4 :
					rptr = request_5;
					break;

				case 5 :
					rptr = request_6;
					break;

				case 6 :
					rptr = request_7;
					break;

				case 7 :
					rptr = request_8;
					break;

				case 8 :
					rptr = request_9;
					break;

				case 9 :
					rptr = request_10;
					break;
					
				default :
					printf("Error: unknown request index\n");
					rptr = NULL;
					break;
			}

			if(rptr == NULL) {
				printf("Server exiting with rptr = NULL\n");
				break;
			}
			else {
				// Print Request
				char s[129];
				int endoffile = 0;
				int flaaaaag = 0;
				printf("Read successful at request %d; request index: %d\nkeyword: ", i, rptr[0]);
				for(int32_t i = 1; i < 128; i++) {
					if(rptr[i] != '#')
						s[i-1] = rptr[i];
					else {
						endoffile = i;
						flaaaaag = 1;
						break;
					}
					fflush(stdout);
				}

				if(flaaaaag == 0)
					s[128] = '\0';
				else
					s[endoffile] = '\0';
					
				printf("%s\n", s);

				// Process Request
				// Version 1: write to a fixed-sized, large-enough buffer
				pthread_t thread;
				int32_t write_address [128] = {0};
				search_keyword = s;
				int create;
				void* status = 0;
				if((create = pthread_create(&thread, NULL, initialize_search, (void*)write_address) < 0)) {
					fprintf(stderr, "Cannot create thread\n");
				}

				pthread_join(thread, &status);
				printf("Search results: ");
				for(int i = 0; i < 128; i++) {
					if(write_address[i] != 0)
						printf("%d ", write_address[i]);
				}
				printf("\n-----------------------------------\n");
			}
		}
	}

	printf("Removing semaphore_queue_state...\n");
	getchar();
	getchar();
	fflush(stdout);

	// Exit Code
	// Unlink SEM01
	int32_t sdestroy = sem_unlink(SEM01);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEM01\n");
	}

	printf("Server exiting...\n");
	exit(0);
}

int search(char* file_name, int32_t* write_address) {
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
}

void* initialize_search(void* ptr){
	int32_t* write_address = (int32_t*)ptr;

	// Synch with client
	
	pthread_exit(search(search_keyword, write_address));
}
