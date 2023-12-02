//main process create a child and pipe. Parent writes in pipe and child reads from pipe

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
	FILE *write_fp;
	char buffer[BUFSIZ + 1];
	sprintf(buffer, "The quick brown fox is sleeping.\n");
	write_fp = popen("cat > newfile.txt", "w");
	if (write_fp != NULL){
		fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
		pclose(write_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
//communication between child and parent
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(){
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "Hello World";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;
	memset(buffer, '\0', sizeof(buffer));
	if (pipe(file_pipes) == 0){
		fork_result = fork();
		if (fork_result == -1){
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}
	else if (fork_result == 0){
		sleep(2);
		data_processed = read(file_pipes[0], buffer, BUFSIZ);
		printf("Child read %d bytes: %s\n", data_processed, buffer);
		exit(EXIT_SUCCESS);
	}
	else{
		data_processed = write(file_pipes[1], some_data, strlen(some_data));
		printf("Parent wrote %d bytes: %s\n", data_processed, some_data);
		}
	}
	exit(EXIT_SUCCESS);
}

//implement pipeline between child and parent in one way

#include<stdio.h>
#include<unistd.h>
int main() {
	int pipefds[2];
	int returnstatus;
	char writemessages[2][20] = {"Hi", "Hello"};
	char readmessage[20];
	returnstatus = pipe(pipefds);
	if(returnstatus == -1) {
		printf("Unable to create pipe\n");
		return 1;
	}
	printf("Writing to pipe - Message 1 is %s\n", writemessages[0]);
	write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
	read(pipefds[0], readmessage, sizeof(readmessage));
	printf("Reading from pipe Message 1 is %s\n", readmessage);

	printf("Writing to pipe - Message 2 is %s\n", writemessages[1]);
	write(pipefds[1], writemessages[1], sizeof(writemessages[1]));
	read(pipefds[0], readmessage, sizeof(readmessage));
	printf("Reading from pipe Message 2 is %s\n", readmessage);
	return 0;
}

//implement IPC between child and parent in both or two way

#include<stdio.h>
#include<unistd.h>
int main(void) {
	int pipefds1[2], pipefds2[2];
	int returnstatus1, returnstatus2;
	int pid;
	char pipe1writemessage[20] = "Hi";
	char pipe2writemessage[20] = "Hello";
	char readmessage[20];
	returnstatus1 = pipe(pipefds1);
	if(returnstatus1 == -1) {
		printf("Unable to create pipe 1 \n");
		return 1;
	}
	returnstatus2 = pipe(pipefds2);
	if(returnstatus2 == -1) {
		printf("Unable to create pipe 2 \n");
		return 1;
	}
	pid = fork();
	if(pid != 0) // Parent process
	{
		close(pipefds1[0]); // Close the unwanted pipe 1 read side
		close(pipefds2[1]); // Close the unwanted pipe 2 write side
		printf("In parent: Writing to pipe 1 - Message is %s\n", pipe1writemessage);
		write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage));
		read(pipefds2[0], readmessage, sizeof(readmessage));
		printf("In Parent: Reading from pipe 2 - Message is %s\n", readmessage);
	}
	else {
		close(pipefds1[1]); // Close the unwanted pipe 1 read side
		close(pipefds2[0]); // Close the unwanted pipe 2 write side
		read(pipefds1[0], readmessage, sizeof(readmessage));
		printf("In Child: Reading from pipe 1 - Message is %s\n", readmessage);
		printf("In Child: Writing to pipe 2 - Message is %s\n", pipe2writemessage);
		write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage));
	}
	return 0;
}
