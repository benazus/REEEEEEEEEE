#include "shared.h"

int element_count = 0;
int read_index = 0;
int write_index = 0;

int main() {
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);

	int32_t* ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

    semaphore_test = sem_open(SEMTEST, O_CREAT | O_EXCL, SEMTEST_PERMISSIONS, 1);
    if(semaphore_test == SEM_FAILED) {
		if(errno != EEXIST) {
			fprintf(stderr, "Cannot open SEM01\n");
			exit(1);
		}
		else {
			fprintf(stderr, "SEMTEST already exists.\n");
            sem_unlink(SEMTEST);
            exit(0);
		}
	}

    int32_t* element_count = ptr + ELEMENT_COUNT_INDEX;
    int32_t* read_index = ptr + READ_INDEX;
    int32_t* write_index = ptr + WRITE_INDEX;

    *element_count = 0;
    *write_index = 0;

    int i = 1;
    int times = 0;

    while(times < 1000) {
	    sem_wait(semaphore_test);

        if(*element_count < 10) {
            printf("element_count: %d\n", *element_count);
            ptr[*write_index] = i;
            *write_index = (*write_index + 1) % 10;
            *element_count = *element_count + 1;
            i++;
            times++;
        }
        else {
            printf("Buffer full, waiting...\n");
        }
	    sem_post(semaphore_test);
        sleep(1);
    }

    *write_index = -1;
}