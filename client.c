#include "shared.h"

int main()
{
	int shm_fd;

	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	shm_fd = shm_open(name, O_RDONLY, 0666);

	int* ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

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
	int* request_10 = ptr + REQUEST_10_START;

	// Test
	printf("%c\n", *queue_state);
	printf("%c\n", *result_queue_1);
	printf("%c\n", *result_queue_2);
	printf("%c\n", *result_queue_3);
	printf("%c\n", *result_queue_4);
	printf("%c\n", *result_queue_5);
	printf("%c\n", *result_queue_6);
	printf("%c\n", *result_queue_7);
	printf("%c\n", *result_queue_8);
	printf("%c\n", *result_queue_9);
	printf("%c\n", *result_queue_10);
	printf("%c\n", *request_1);
	printf("%c\n", *request_2);
	printf("%c\n", *request_3);
	printf("%c\n", *request_4);
	printf("%c\n", *request_5);
	printf("%c\n", *request_6);
	printf("%c\n", *request_7);
	printf("%c\n", *request_8);
	printf("%c\n", *request_9);
	printf("%c\n", *request_10);
	ptr += SHM_INCREMENT;
	

	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}