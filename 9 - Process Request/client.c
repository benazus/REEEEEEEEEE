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
	if ((ptr == mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0) == -1)) {
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

	semaphore_queue_state = sem_open(SEM01, 0);

	// Write a request
	printf("Client waiting...\n");
	int32_t wait = sem_wait(semaphore_queue_state);
	printf("Client received semaphore_queue_state\n");
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
	printf("Exitting critical section...\n");
	//getchar();
	printf("Client releasing semaphore_queue_state...\n");
	int32_t post = sem_post(semaphore_queue_state);
	printf("Client released semaphore_queue_state.\n");

	if(resq == -1) {
		printf("Error: Cannot find available result queue\n");
	}
	else {
		int32_t* rptr;

		switch(resq) {
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
				printf("Error: unknown result_queue index\n");
				rptr = NULL;
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

			for(int32_t i = 11; i < 128; i++)
				rptr[i] = '#';
			printf("Client finished writing.\n");
		}
	}

	// End of writing the request

	/*if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}*/

	printf("Client exiting...\n");
	return 0;
}