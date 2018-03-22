#include "shared.h"

int main() {
	// Open Shared Memory
	int shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

    int32_t* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
	if ((ptr == MAP_FAILED)) {
		printf("Map failed\n");
		return -1;
	}

    semaphore_test = sem_open(SEMTEST, 0);

    int32_t* element_count = ptr + ELEMENT_COUNT_INDEX;
    int32_t* read_index = ptr + READ_INDEX;
    int32_t* write_index = ptr + WRITE_INDEX;

    while(*write_index != -1){
        sem_wait(semaphore_test);
        if(*element_count > 0) {
            printf("read_value: %d\n", ptr[*read_index]);
            *element_count = *element_count - 1;
            *read_index = (*read_index + 1) % 10;
        }
        sem_post(semaphore_test);
        sleep(1);
    }

    if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}
}