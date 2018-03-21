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

int main()
{
    const int SIZE = 4096;
    const char* name = "OS";
    int shm_fd;
    int i;
    void* ptr;

    shm_fd = shm_open(name, O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    i=0;
    while(i < 10) {
        printf("%d\n", ptr[i]);
        i++;
    }

    shm_unlink(name);
    return 0;
}