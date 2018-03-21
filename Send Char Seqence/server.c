#include "shared.h"

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "Studying ";
	const char *message1= "Operating Systems ";
	const char *message2= "Is Fun!";

	int shm_fd;

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	int* ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	ptr[0] = 4;
	ptr[1] = 11;
	ptr[2] = 'b';
	ptr[3] = 'e';
	ptr[4] = 'r';
	ptr[5] = 'a';
	ptr[6] = 't';
	ptr[7] = ' ';
	ptr[8] = 'b';
	ptr[9] = 'i';
	ptr[10] = 'c';
	ptr[11] = 'e';
	ptr[12] = 'r';
	ptr += sizeof(int) * 7;
	return 0;
}