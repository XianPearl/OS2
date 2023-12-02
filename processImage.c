// demonstrate the application of execvp()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	char* command = "ls";
	char* argument_list[] = {"ls", "-l", NULL};
	printf("Before calling execvp()\n");
	// Calling the execvp() system call
	int status_code = execvp(command, argument_list);
	if(status_code == -1) {
		printf("Process did not terminate correctly\n");
		exit(1);
	}
	/*This part after execvp() does not execute at all, since "ls -l" took control of the process*/
	printf("This line will not be printed if execvp() runs correctly\n");
	return 0;
}

//demonstrate the application of the execvp() by calling it inside a child process

#include <stdio.h>
#include <unistd.h>
int main() {
	char* command = "ls";
	char* argument_list[] = {"ls", "-l", NULL};
	printf("Before calling execvp()\n");
	printf("Creating another process using fork()...\n");
	if(fork() == 0) {
		// Newly spawned child process. This will be taken over by "ls -l"
		int status_code = execvp(command, argument_list);
		printf("ls -l has taken control of this child process. This won't execute unless it terminates abnormally!\n");
		if(status_code == -1) {
			printf("Terminated Incorrectly\n");
			return 1;
		}
	}
	else {
		//Old parent process. The C program will come here
		printf("This line will be printed\n");
	}
	return 0;
}

//demonstrate the working of 'execl()' function w.r.t process

#include <stdio.h>
#include <unistd.h>

int main() {
	char* const_ps_envp[] = {"PATH=/bin:/usr/bin", "TERM=console", 0};
	printf("Before execl\n");
	execl("/bin/ps", "ps", "-a", NULL);
	printf("After execlp\n");
}

// WAP in C to swap 1 running process with another using the 'execv()'

//child.c
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("I am the child process\n");

	printf("Argument 1: %s\n", argv[1]);
	printf("Argument 2: %s\n", argv[2]);
	printf("Argument 3: %s\n", argv[3]);
}

//parent.c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
	printf("I am the parent process\n\n");

	char *arg_Ptr[4];
	arg_Ptr[0] = "child.c";
	arg_Ptr[1] = "Hello from the child process";
	arg_Ptr[2] = "Good-Bye from the child process";
	arg_Ptr[3] = NULL;

	execv("Cexecv", arg_Ptr);
	printf("Error: %i\n", errno);
}
