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

#define N 10

#define QUEUE_STATE_START 0
#define RESULT_QUEUE_1_START 11
#define RESULT_QUEUE_2_START 51
#define RESULT_QUEUE_3_START 91
#define RESULT_QUEUE_4_START 131
#define RESULT_QUEUE_5_START 171
#define RESULT_QUEUE_6_START 211
#define RESULT_QUEUE_7_START 251
#define RESULT_QUEUE_8_START 291
#define RESULT_QUEUE_9_START 331
#define RESULT_QUEUE_10_START 371
#define REQUEST_1_START 411
#define REQUEST_2_START 539
#define REQUEST_3_START 667
#define REQUEST_4_START 795
#define REQUEST_5_START 923
#define REQUEST_6_START 1051
#define REQUEST_7_START 1179
#define REQUEST_8_START 1307
#define REQUEST_9_START 1435
#define REQUEST_10_START 1563
#define SHM_INCREMENT 1690

sem_t semaphore_queue_state;

const char *name = "shm";
const int SIZE = 8192; // !!! - 4096 is not enough