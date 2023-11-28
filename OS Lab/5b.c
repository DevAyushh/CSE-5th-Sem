#include<stdio.h>
#include<unistd.h>
void main() 
{
	int id=fork();
	if(id > 0)
	{
		printf("Parent PID : %d  PPID : %d\n" , getpid(),getppid());
		sleep(7);
		printf("Parent Killed\n");
	}
	else if(id==0)
	{
		printf("Child PID : %d  PPID : %d\n" , getpid(),getppid());
		sleep(15);
	}
	
	else
		printf("Error encountered ");
}
		
