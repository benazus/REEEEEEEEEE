#include <semaphore.h>
struct request {
    sem_t* semaphore;
    char* keywords;
};

    /*struct request request_queue[1];
    char* x = argv[1];
    sprintf(x, "%s", "1"); // !!!!!
    sem_t* semaphore = sem_open(x, O_CREAT);
    int i = sem_init(semaphore, 1, 1);
    if(i != 0){
        fprintf(stderr, "Error in initializing semaphore");
        exit(0);
    }*/

    /*request_queue[0].semaphore = semaphore;
    request_queue[0].keywords = "beratbiçer";*/
    /* 
        int sem_post(sem_t *sem);
            sem_post() returns 0 on success; on error, the value of  the  semaphore
            is  left  unchanged,  -1  is returned, and errno is set to indicate the
            error.
        int sem_wait(sem_t *sem);
            All of these functions return 0 on success; on error, the value of  the
            semaphore  is left unchanged, -1 is returned, and errno is set to indi‐
            cate the error.
    */



    /*printf("%ld", strtol(((char *)ptr), NULL, 10));
    
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    
    printf("%ld", strtol(((char *)ptr), NULL, 10));*/

    //struct request* ptr = (struct request*)malloc(sizeof(struct request));