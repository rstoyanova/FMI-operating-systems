//
// program takes 2 arguments file to copy and a filename for the copy
//

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main(int args, char* argv[]) {
	
	if (args !=3) {
		write(2, "Wrong number of arguments\n", 25);
	}

	int fd_from;
	int fd_to;
	const char* filename_from = argv[1];
	const char* filename_to = argv[2];
	char c;


	if ((fd_from = open(filename_from, O_RDONLY)) == -1) {
		write(2, "File failed to open in read mode\n", 33);
		close(fd_from);
		exit(-1);
	}
	if ((fd_to = open(filename_to, O_CREAT|O_WRONLY)) == -1) {
		write(2, "File failed to open in write mode\n", 34);
		close(fd_to);
		exit(-1); 
	} 

	while (read(fd_from, &c, 1)) {
		write(fd_to, &c, 1);
	}

	close(fd_from);
	close(fd_to);
	exit(0);
}	
