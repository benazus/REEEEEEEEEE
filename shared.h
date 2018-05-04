#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

#define N 10
#define BUFFER_SIZE 101
#define MAX_KEYWORD 128
#define MAX_LINE 1024
#define MAX_FILENAME 128
#define MAX_SEMNAME 128
#define MAX_SHMNAME 128
#define MIN_LINENO 1

typedef struct search_arguments {
	char* keyword;
	int32_t index;
	struct shared_memory_segment* shared_memory;
	sem_t* semaphore;
} search_arguments;

typedef struct search_request {
    char keyword[128];
    int  index;
} search_request;

typedef struct search_request_queue {
    search_request requests[N + 1];
    int in;
    int out;
} search_request_queue;

typedef struct search_result_queue {
    int data[BUFFER_SIZE + 1];
    int in;
    int out;
} search_result_queue;

typedef struct shared_memory_segment {
    search_request_queue search_request_queue;
    search_result_queue search_result_queue[N];
    int search_queue_state[N];
} shared_memory_segment;

#define SEM_PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

const char *name = "osp2_shm";