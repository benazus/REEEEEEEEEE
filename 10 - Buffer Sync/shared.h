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

const char *name = "memory";
const int SIZE = 60;

#define ELEMENT_COUNT_INDEX 41
#define READ_INDEX 45
#define WRITE_INDEX 49

#define SEMTEST "/semtest"
#define SEMTEST_PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
sem_t* semaphore_test;