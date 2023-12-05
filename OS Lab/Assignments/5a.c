#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
	pid_t id=fork();
	sleep(5);
	if (id > 0)
	{
		printf("\nParent Process: PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(10);
	}
	else if (id == 0)
	{
		printf("\nChild Process: PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(10);
	}
	else
	{
		printf("Error!");
		exit(0);
	}
}
