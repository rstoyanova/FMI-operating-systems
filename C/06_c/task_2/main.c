//
//head without flags
//

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		write(2, "Wrong number of arguments\n", 26);
	}
	
	int fd;
	char c;

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		write (2, "File didn't open", 16);
		close(fd);
		exit(-1);
	}

	int cntr = 0;

	while (cntr != 10) {
		read(fd, &c, 1);
		write(1, &c, 1);

		if (c == '\n') {
			cntr++;
		}
	}

	close(fd);
}
