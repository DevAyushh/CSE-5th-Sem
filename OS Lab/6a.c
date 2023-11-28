#include<stdio.h>
#include<unistd.h>
# define maxsize 100
void main()
{
    int pid;
    int pfd[2];
    int ret=pipe(pfd);
    char msg[maxsize];
    char msg_rev[maxsize+1];
    pid=fork();
    if(pid==0)
    {
        close(pfd[0]);
        printf("Now in child process, Enter the message\n");
        scanf("%99[^\n]",msg);
        write(pfd[1],msg,sizeof(msg));
        close(pfd[1]);
    }
    else
    {
        close(pfd[1]);
        read(pfd[0],msg_rev,sizeof(msg));
        printf("The message received in parent process is: %s\n",msg_rev);
        close(pfd[0]);
    }
}
