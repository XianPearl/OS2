// Write a program to implement orphan process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main() {
	int child_pid = fork();
	if(child_pid < 0) { printf("fork failed."); }
	else if(child_pid == 0) {
		printf("Inside child process with PID: %d\n", getpid());
		printf("Parent process: %d\n", getppid());
		sleep(10);
		printf("child process is done.\n");
	}
	else {
		printf("Parent process is running %d \n", getpid());
		printf("Parent process is done.\n");
	}
	return 0;
}

// Write a program to implement and create a zombie process.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main() {
	int p = fork();
	if(p == 0) {
		printf("Inside child process.\n");
		printf("PID = %d \n", getpid());
		printf("PPID = %d \n", getppid());
	}
	else if(p > 0) {
		sleep(10);
		printf("Parent process");
		printf("PID = %d \n", getpid());
		printf("PPID = %d \n", getppid());
		printf("Zombie process. \n");
	}
	while(1) { 
    printf("Valid"); 
  }
}

// Write a program to implement and explain how creation of zombie process can be avoided

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main() {
	int pid = fork();
	if(pid < 0) 
    printf("Fork failed");
	else if(pid == 0) {
		printf("Child process is running with PID %d\n", getpid());
		sleep(2);
		printf("Child process is done.\n");
	}
	else{
		printf("Parent process with PID %d is running \n", getpid());
		int status;
		wait(&status);
		printf("Parent process is done.\n");
	}
	return 0;
}
