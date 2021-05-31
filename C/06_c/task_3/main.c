// wc with 3 posible flags
// -w / word count
// -m / char count
// -l / line count



#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>

#include <string.h>

int main(int argc, char* argv[]) {

	if (argc != 3) {
		write(2, "Wrong number of arguments\n", 26);
		exit(-1);
	}

	int fd;
	int cntr = 0;
	char c;	
	
	if (( fd = open(argv[2], O_RDONLY)) == -1) {
		write(2, "File didn't open", 16);
		close(fd);
		exit(-1);
	}
	
	if ((strcmp(argv[1], "-m")) == 0) {
		while ( read(fd, &c, 1)) {
			if (c != '\n') {
				cntr++;
			}
		}
		printf("Number of chars %d\n", cntr);
		
	} else if ((strcmp(argv[1], "-l")) == 0) {
		while ( read(fd, &c, 1)) {
			if(c == '\n') {
				cntr++;
			}
		}
		printf("Number of lines %d\n", cntr);
	} else if ((strcmp(argv[1], "-w")) == 0) {
		while ( read(fd, &c, 1)) {
			if (c == ' ' ||
			    c == '\n') {
				cntr++;
			}
		}
		printf("Number of words %d\n", cntr);
	} else {
		write(2, "Wrong flag\n", 10);
	}

	
	close(fd);
	exit(1);
}



