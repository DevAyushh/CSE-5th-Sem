#include<stdio.h>
#include<unistd.h>

void main()
{
	int p;
	p=fork();
	if (p > 0)
	{
		printf("\nParent Process: PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(10);
	}
	else if (p == 0)
	{
		printf("\nChild Process: PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(10);
	}
	else
		printf("Error!")
}
