//
// Да се напише програма на C, която получава като параметри от команден ред две команди (без параметри) 
// и име на файл в текущата директория. Ако файлът не съществува, го създава. 
// Програмата изпълнява командите последователно, по реда на подаването им. 
// Ако първата команда завърши успешно, програмата добавя нейното име към съдържанието на файла, подаден като команден параметър. 
// Ако командата завърши неуспешно, програмата уведомява потребителя чрез подходящо съобщение
//

#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

const int CORRECT_NUM_OF_ARG = 4;

int main(int argc, char* argv[]) {
	
	if (argc != CORRECT_NUM_OF_ARG) {
		err(1, "Invalid number of arguments!\n");
	}

	int fd;
	if ((fd = open(argv[3], O_CREAT|O_TRUNC|O_WRONLY, 0777)) == -1) {
		err(2, "File did't open in write mode!\n");
	}

	if ((fork()) == 0) {
		if ((execlp(argv[1], argv[1], ((char*) NULL))) == -1) {
			err(3, "Command didn't exec!\n");
		}
	}

	int stat;
	wait(&stat);

	if (WIFEXITED(stat)) {
		if (WEXITSTATUS(stat) == 0) {
			write(fd, argv[1], (strlen(argv[1])));
		} else {
			printf("Fist command didn't exec!\n");
		}
	}

	if ((fork()) == 0) {
		if ((execlp(argv[2], argv[2], ((char*) NULL))) == -1) {
			err(4, "Command didn't exec!\n");
		}
	}

	wait(&stat);
	close(fd);
	exit(0);
}



