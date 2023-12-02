#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void *thread_function(void *arg);
char message[]="OS Assignment 8";
int main(){
  int res;
	pthread_t a_thread;
	void *thread_result;
	res=pthread_create(&a_thread,NULL,thread_function,message);
	if(res != 0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("\nWaiting for thread to finish");
	res=pthread_join(a_thread,&thread_result);
	if(res != 0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("\nThread joined ,it returned %s\n",(char *)thread_result);
	printf("\nMessage is now %s\n",message);
	exit(EXIT_SUCCESS);
	return 0;
}
void *thread_function(void *arg){
	printf("\nThread_function is running. Argument is %s",(char*)arg);
	sleep(3);
	strcpy(message,"closed.");
	pthread_exit("\nThank you for the CPU time");
}
