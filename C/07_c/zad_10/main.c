//Да се напише програма на C, която получава като параметри от команден ред две команди (без параметри). 
//Изпълнява първата. Ако тя е завършила успешно изпълнява втората. Ако не, завършва с код 42

#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int CORRECT_NUM_OF_ARG = 3;

int main(int argc, char* argv[]) {

	if (argc != CORRECT_NUM_OF_ARG) {
		err(1, "Illiegal number of arguments!\n");
	}
	
	pid_t child_pid;
	
	if ((child_pid = fork()) == 0) {
		if ((execlp(argv[1], argv[1], ((char*) NULL))) == -1) {
			err(2, "First command didn't exec!\n");
		}	
	} else {
		int stat;
		
		//waitpid(child_pid, &stat, 0);
		wait(&stat);

		if (WIFEXITED(stat)) {
			if ((WEXITSTATUS(stat)) == 0) {
				if((fork()) == 0) {
					if((execlp(argv[2], argv[2], ((char*) NULL))) == -1) {
						err(3, "Second command didn't exec!\n");
					}
				}
			} else {
				exit(42);
			}
	
		} else {
			exit(42);
		}
	}

	exit(0);
}

