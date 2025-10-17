#include<stdio.h>
#include<unistd.h>
int main(){
	pid_t firstFork = fork();
	pid_t secondFork = fork();
	pid_t thirdFork = fork();
	printf("Parent ID: %d, Process ID: %d\n", getppid(),getpid());
	return 0;
}
