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

#define SEMQS "/semaphore_queue_state"
#define SEMCT1 "/client_thread_1"
#define SEMCT2 "/client_thread_2"
#define SEMCT3 "/client_thread_3"
#define SEMCT4 "/client_thread_4"
#define SEMCT5 "/client_thread_5"
#define SEMCT6 "/client_thread_6"
#define SEMCT7 "/client_thread_7"
#define SEMCT8 "/client_thread_8"
#define SEMCT9 "/client_thread_9"
#define SEMCT10 "/client_thread_10"
#define SEM_PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

sem_t* semaphore_queue_state;
sem_t* client_thread_1;
sem_t* client_thread_2;
sem_t* client_thread_3;
sem_t* client_thread_4;
sem_t* client_thread_5;
sem_t* client_thread_5;
sem_t* client_thread_6;
sem_t* client_thread_7;
sem_t* client_thread_8;
sem_t* client_thread_9;
sem_t* client_thread_10;

const char *name = "shm";
const int SIZE = 16384; // !!! - 4096 and lower causes bugs in accessing shared memory
#define FILE_NAME "test.txt"

#define RQ1_ELEMENT_COUNT_INDEX 1721
#define RQ1_READ_INDEX 1725
#define RQ1_WRITE_INDEX 1729
#define RQ2_ELEMENT_COUNT_INDEX 1733
#define RQ2_READ_INDEX 1737
#define RQ2_WRITE_INDEX 1741
#define RQ3_ELEMENT_COUNT_INDEX 1745
#define RQ3_READ_INDEX 1749
#define RQ3_WRITE_INDEX 1753
#define RQ4_ELEMENT_COUNT_INDEX 1757
#define RQ4_READ_INDEX 1761
#define RQ4_WRITE_INDEX 1765
#define RQ5_ELEMENT_COUNT_INDEX 1769
#define RQ5_READ_INDEX 1773
#define RQ5_WRITE_INDEX 1777
#define RQ6_ELEMENT_COUNT_INDEX 1781
#define RQ6_READ_INDEX 1785
#define RQ6_WRITE_INDEX 1789
#define RQ7_ELEMENT_COUNT_INDEX 1793
#define RQ7_READ_INDEX 1797
#define RQ7_WRITE_INDEX 1801
#define RQ8_ELEMENT_COUNT_INDEX 1805
#define RQ8_READ_INDEX 1809
#define RQ8_WRITE_INDEX 1813
#define RQ9_ELEMENT_COUNT_INDEX 1817
#define RQ9_READ_INDEX 1821
#define RQ9_WRITE_INDEX 1825
#define RQ10_ELEMENT_COUNT_INDEX 1829
#define RQ10_READ_INDEX 1833
#define RQ10_WRITE_INDEX 1837

#define SIGNAL_1 1841
#define SIGNAL_2 1845
#define SIGNAL_3 1849
#define SIGNAL_4 1853
#define SIGNAL_5 1857
#define SIGNAL_6 1861
#define SIGNAL_7 1865
#define SIGNAL_8 1869
#define SIGNAL_9 1873
#define SIGNAL_10 1877