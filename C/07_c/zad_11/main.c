//Да се напише програма на C, която изпълнява последователно подадените ѝ като параметри команди, като реализира следната функционалност постъпково:

    //main cmd1 ... cmdN Изпълнява всяка от командите в отделен дъщерен процес.
    //... при което се запазва броя на изпълнените команди, които са дали грешка и броя на завършилите успешно.


#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	int num_of_err = 0;
	int num_of_exec_succ = 0;

	for(int i=1; i<argc; i++) {
		if ((fork()) == 0) {
			if ((execlp(argv[i], argv[i], ((char*) NULL))) == -1) {
				err(2, "Didn't exec!\n");
			}

		} else {
			int stat;
			wait(&stat);
			if (WIFEXITED(stat)) {
				if ((WEXITSTATUS(stat)) == 0) {
					num_of_exec_succ++;
				} else {
					num_of_err++;
				}
			} else {
				num_of_err++;
			}
		}
	}

	printf("Number of successfully executed commands: %d \nNumber of err: %d\n", 
		num_of_exec_succ, num_of_err);
	exit(0);
}
