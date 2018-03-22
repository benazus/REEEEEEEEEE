#include "shared.h"

int main()
{	
	// Shared Memory Initialization
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);

	int* ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	// Shared memory data segments
	int* orig = ptr;
	int* queue_state = ptr + QUEUE_STATE_START;
	int* result_queue_1 = ptr + RESULT_QUEUE_1_START;
	int* result_queue_2 = ptr + RESULT_QUEUE_2_START;
	int* result_queue_3 = ptr + RESULT_QUEUE_3_START;
	int* result_queue_4 = ptr + RESULT_QUEUE_4_START;
	int* result_queue_5 = ptr + RESULT_QUEUE_5_START;
	int* result_queue_6 = ptr + RESULT_QUEUE_6_START;
	int* result_queue_7 = ptr + RESULT_QUEUE_7_START;
	int* result_queue_8 = ptr + RESULT_QUEUE_8_START;
	int* result_queue_9 = ptr + RESULT_QUEUE_9_START;
	int* result_queue_10 = ptr + RESULT_QUEUE_10_START;
	int* request_1 = ptr + REQUEST_1_START;
	int* request_2 = ptr + REQUEST_2_START;
	int* request_3 = ptr + REQUEST_3_START;
	int* request_4 = ptr + REQUEST_4_START;
	int* request_5 = ptr + REQUEST_5_START;
	int* request_6 = ptr + REQUEST_6_START;
	int* request_7 = ptr + REQUEST_7_START;
	int* request_8 = ptr + REQUEST_8_START;
	int* request_9 = ptr + REQUEST_9_START;
	int* request_10 = ptr  +REQUEST_10_START;

	// Queue State Initialization
	for(int i = 0; i < N; i++) {
		queue_state[i] = 0;
	}

	// Queue State Semaphore Initialization
	if((semaphore_queue_state = sem_open(SEM01, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
		fprintf(stderr, "Cannot open SEM01\n");
		exit(1);
	}

	

	// Exit Code
	// Unlink SEM01
	int sdestroy = sem_unlink(SEM01);
	if(sdestroy == -1) {
		fprintf(stderr, "Cannot unlink SEM01\n");
	}
	exit(0);
}