#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* f1(void* ptr);

int main() {
    pthread_t thread1;
    int32_t* result = (int*)malloc(sizeof(int32_t) * 10);
    for(int i = 0; i < 10; i++)
        result[i] = i;

    int create;
    void* status = 0;

    if((create = pthread_create(&thread1, NULL, f1, (void*)result)) < 0) {
        fprintf(stderr, "Error in creating thread1\n");
        exit(1);
    }

    pthread_join(thread1, &status);
    free(result);
    exit(0);
}

void* f1(void* result) {
    for(int i = 0; i < 10; i++) {
        printf("%d\n", ((int32_t*)result)[i]);
    }

    pthread_exit(0);
}