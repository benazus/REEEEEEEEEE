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
	int* ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	for(int i = 0; i < N; i++) {
		printf("%d\n", *ptr);
		ptr++;
	}


	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}