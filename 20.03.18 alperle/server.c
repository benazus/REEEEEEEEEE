#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include "shareddata.h"

#define SIZE 4096
#define N 10

const char* name = "OS";
void* ptr;
int shm_fd;
int* queueStates;

int main(int argc, char* argv[]) {
    char* a = argv[1], b = argv[2], c = argv[3];
    queueStates = (int*)malloc(N * sizeof(int));
    
    for(int i = 0; i < N; i++) {
        queueStates[i] = i;
        printf("%d\n", queueStates[i]);
    }

    //printf("%s %s %s", argv[1], argv[2], argv[3]);
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    sprintf(ptr, "%s", (char*) &queueStates);
    printf("%s\n", (char*) (&queueStates));
    while(1);
    free(queueStates);  
    return 0;
}