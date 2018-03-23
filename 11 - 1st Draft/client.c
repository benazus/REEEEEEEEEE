#include "shared.h"

int main()
{
	// Open Shared Memory
	int shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	int32_t* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
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

	semaphore_queue_state = sem_open(SEMQS, 0);
	client_thread_1 = sem_open(SEMCT1, 0);
	client_thread_2 = sem_open(SEMCT2, 0);
	client_thread_3 = sem_open(SEMCT3, 0);
	client_thread_4 = sem_open(SEMCT4, 0);
	client_thread_5 = sem_open(SEMCT5, 0);
	client_thread_6 = sem_open(SEMCT6, 0);
	client_thread_7 = sem_open(SEMCT7, 0);
	client_thread_8 = sem_open(SEMCT8, 0);
	client_thread_9 = sem_open(SEMCT9, 0);
	client_thread_10 = sem_open(SEMCT10, 0);

	int32_t* rptr;
	int32_t* element_count;
	int32_t* read_index;
	int32_t* write_index;
	sem_t* semaphore;
	int32_t* signal_client;

	// Write a request
	int32_t wait = sem_wait(semaphore_queue_state);
	// Critical section
	int32_t resq = -1;
	for(int32_t i = 0; i < N; i++) {
		if(orig[i] == 0) {
			resq = i;
			orig[i] = 1;
			break;
		}
	}
	// End of critical section
	int32_t post = sem_post(semaphore_queue_state);

	if(resq == -1) {
		printf("Error: Cannot find available result queue\n");
	}
	else {
		switch(resq) {
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
			printf("Client exiting with rptr = NULL\n");
		}
		else {
			printf("Client writing...\n");
			rptr[0] = resq;
			rptr[1] = 'b';
			rptr[2] = 'e';
			rptr[3] = 'r';
			rptr[4] = 'a';
			rptr[5] = 't';
			rptr[6] = 'b';
			rptr[7] = 'i';
			rptr[8] = 'c';
			rptr[9] = 'e';
			rptr[10] = 'r';
			rptr[11] = '\0';
			/*for(int32_t i = 11; i < 128; i++) {
				rptr[i] = '\0';
				break;
			}*/

			/*rptr[0] = resq;
			for(int32_t i = 1; i < 128; i++)
				rptr[i] = 'A';*/
			printf("Client finished writing.\n");
		}
	}
	printf("Client: ");
	while(ptr[*write_index] != -1) {
		sem_wait(semaphore);
		if(*element_count > 0) {
			printf("%d ", ptr[*read_index]);
			fflush(stdout);
			*element_count = *element_count - 1;
			*read_index = (*read_index + 1) % 10;
		}	
		sem_post(semaphore);
        sleep(1);
	}

	printf("\nClient exiting...\n");

	/*if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}*/
	
	return 0;
}