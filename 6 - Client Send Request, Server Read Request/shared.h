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

#define RESULT_QUEUE_1_START 41
#define RESULT_QUEUE_2_START 81
#define RESULT_QUEUE_3_START 121
#define RESULT_QUEUE_4_START 151
#define RESULT_QUEUE_5_START 201
#define RESULT_QUEUE_6_START 241
#define RESULT_QUEUE_7_START 281
#define RESULT_QUEUE_8_START 321
#define RESULT_QUEUE_9_START 361
#define RESULT_QUEUE_10_START 401
#define REQUEST_1_START 441
#define REQUEST_2_START 569
#define REQUEST_3_START 697
#define REQUEST_4_START 825
#define REQUEST_5_START 953
#define REQUEST_6_START 1081
#define REQUEST_7_START 1209
#define REQUEST_8_START 1337
#define REQUEST_9_START 1465
#define REQUEST_10_START 1593
#define IS_EMPTY_REQUEST 1720
#define SHM_INCREMENT 1721


#define SEM01 "/sem01"
#define SEM01_PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
sem_t* semaphore_queue_state;

const char *name = "shm";
const int SIZE = 8192; // !!! - 4096 is not enough