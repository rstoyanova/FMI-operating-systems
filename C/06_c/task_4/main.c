//
// takes 2 arguments / filenames
// swaps the content
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdlib.h>

#include <err.h>

#include <stdio.h>

int main(int argc, char* argv[]) {

	if (argc != 3) {
		err(1, "Illegal number of arguments!\n");
	}

	int fd1;
	int fd2;
	int swapper;
	char c;
	
	// copying content from first file to swapper
	//	
	if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
		err(2, "File %s didn't open in read mode\n", argv[1]);
	}

	if ((fd2 = open(argv[2], O_RDONLY)) == -1) {
		close(fd1);
		err(3, "File %s didn't open in read mode\n", argv[2]);
	}


	if ((swapper = open("swapper.txt", O_CREAT|O_TRUNC|O_WRONLY, 0777)) == -1) {
		err(4, "Swapper file didn't open in write mode\n");
	}
	
	while(read(fd1, &c, 1)) {
		write(swapper, &c, 1);
	}

	// copying content from second file to the first
	//
	if ((close(fd1)) == -1) {
		err(5, "Error\n");
	}

	if ((fd1 = open(argv[1], O_WRONLY|O_TRUNC)) == -1) {
		close(fd2);
		close(swapper);
		err(6, "File %s didn't open in write mode!\n", argv[1]);
	}

	while(read(fd2, &c, 1)) {
		write(fd1, &c, 1);
	}

	close(fd1);

	// copying content of first file from swapper to second file
	//
	if ((close(swapper)) == -1) {
		err(7, "Error\n");
	}

	if ((swapper = open("swapper.txt", O_RDONLY, 0777)) == -1) {
		close(fd2);
		err(8, "Swapper file didn't open in read mode\n");
	}

	if ((close(fd2)) == -1) {
		err(9, "Error");
	}

	if ((fd2 = open(argv[2], O_WRONLY|O_TRUNC)) == -1) {
		close(swapper);
		err(10, "File %s didn't open in write mode!\n", argv[2]);
	}

	while(read(swapper, &c, 1)) {
		write(fd2, &c, 1);
	}

	// getting rid of the swapper
	//
	if ((remove("swapper.txt")) == -1) {
		close(fd2);
		err(11, "Swapper file wasn't deleted!\n");
	}

	close(fd2);

	exit(12);



}
