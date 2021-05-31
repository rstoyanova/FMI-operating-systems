#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	if ((execl("/bin/date", "date")) == -1) {
		err(2,"err");
	} else {
		printf("Success!\n");
	}
		
	exit(0);
}
