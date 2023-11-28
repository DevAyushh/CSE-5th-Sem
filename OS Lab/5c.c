#include<stdio.h>
#include<unistd.h>
void main()
{
    int p;
    p=fork();
    if(p > 0)
    {
        printf("\nParent process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(15);
        printf("Parent gets the news\n");
	    wait(8);
    }
    else if (p == 0)
    { 
	printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(7);
        printf("Now the child process is killed and it becomes a zombie process\n");
    }
    else
    	printf("Error!");
}
