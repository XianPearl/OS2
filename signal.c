// Write a program to kill the process using SIGKILL signal.

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
int main() {
	pid_t target_pid;
	printf("Enter the pid of the process to kill: ");
	scanf("%d", &target_pid);
	if(kill(target_pid, SIGKILL) == 0) printf("Process with pid %d has been killed", target_pid);
	else printf("Error");
	return 0;
}

// Demonstrate the orphan process is created using SIGKILL

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main(void) {
	pid_t ppid, pid, cid;
	ppid = getpid();
	pid = fork();
	if(ppid == getpid()) printf("Parent\n");
	else if(cid == getpid()) printf("Child\n");
	if(pid > 0) {
		int i = 0; 
		while(i++ < 5) {
			printf("In the parent process.\n");
			sleep(1);
		}
	}
	else if(pid == 0) {
		int i = 0;
		while(i++ < 10){
			printf("In the child process.\n");
			sleep(1);
		}
		if(i == 3) {
			kill(ppid, SIGKILL);
			printf("Parent killed, I am orphaned!\n");
		}
	}
	else {
		printf("Something bad happened.");
		exit(EXIT_FAILURE);
	}
	return 0;
}

// Write a program to stop the esecution of a parent process using SIGSTOP signal from the child process.
// Resume the execution oof parent process using SIGCONT process.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main() {
	pid_t pid, ppid;
	pid = fork();
	if(pid > 0) {
		printf("Inside parent.\n");
		sleep(5);
		printf("Parent process done.\n");
	}
	else if(pid == 0) {
		ppid = getpid();
		printf("Inside child process\n");
		kill(ppid, SIGSTOP);
		printf("Parent stopped\n");
		sleep(5);
		kill(ppid, SIGCONT);
		printf("Parent resumed\n");
	}
	else { printf("Error"); }
}

// WAP to change thge default func of Ctrl+C. Later restore it again.

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int i=2;
void oh(int sig) {
    printf("Pressed Ctrl+C\n");
    i--;
    signal(SIGINT,oh);
    if(i==0) {
        printf("Restoring to default.\n");
        signal(SIGINT,SIG_DFL);
    }
int main() {
    signal(SIGINT, oh);
    while(1) {
        printf("Hello World!\n");
        sleep(1);
    }
}
