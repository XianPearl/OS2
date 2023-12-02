// Write a program ro implement parent-child procedure and explain their concurrent execution

#include<stdio.h>
#include<unistd.h>
void main() {
	int pid;
	pid = fork();
	if(pid == 0) 
    printf("Child PID: %d   Child PPID: %d   \n", getpid(), getppid());
	else if(pid > 0) 
    printf("Parent PID: %d   Parent PPID: %d   \n", getpid(), getppid());
  else
    printf("Process is not created");
}

// Write a C program to take a child process, take one variable and show its changes in child and parent process

#include<stdio.h>
#include<unistd.h>
int global = 100;
static int b = 1000;
void main() {
	int local = 10, pid;
	pid = fork();
	if(pid == 0) {
		printf("Child PID: %d   Child PPID: %d   \n", getpid(), getppid());
		printf("Static = %d \n", --b);
		printf("Global = %d \n", --global);
		printf("Local = %d \n", --local);
	}
	else if(pid > 0) {
		printf("Parent PID: %d   Parent PPID: %d   \n", getpid(), getppid());
		printf("Static = %d \n", ++b);
		printf("Global = %d \n", ++global);
		printf("Local = %d \n", ++local);
	}
	sleep(10);
}

// WAP to create 8 process using minimum fork

#include<stdio.h>
#include<unistd.h>
void main() {
	printf("Parent Process ID = %d\n", getpid());
  for (int i = 0; i < 3; i++) {
    if (fork() == 0)
      printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
  }
	sleep(1);
}
