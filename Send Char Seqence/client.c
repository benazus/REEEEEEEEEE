#include "shared.h"

int main()
{
	const char *name = "OS";
	const int SIZE = 4096;

	int shm_fd;

	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}
	/* create the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);

	/* now map the shared memory segment in the address space of the process */
	int* ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	int semaphore_index = ptr[0];
	int keyword_size = ptr[1];
	printf("semaphore_index: %d, keyword_size: %d\nkeyword: ", semaphore_index, keyword_size);
	for(int j = 2; j < ptr[1] + 2; j++)
		printf("%c", ptr[j]);
	printf("\n");
	

	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}