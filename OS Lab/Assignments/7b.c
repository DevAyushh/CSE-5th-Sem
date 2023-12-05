#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

void alarm_handler(int signum)
{
    printf("The child process has sent a signal to the parent process with signal number: %d\n", signum);
}

void main()
{
    signal(SIGALRM, alarm_handler);
    pid_t id=fork();

    if (id == -1)
    {
        perror("fork");
        exit(1);
    }

    if (id == 0)
    {
        printf("Child process with PID %d and PPID %d is running...\n", getpid(), getppid());
        printf("Child process will send an alarm to parent.\n");
        sleep(5);
        kill(getppid(), SIGALRM);
        exit(0); // Child process exits after sending the signal
    }
    else
    {
        printf("Parent process with PID %d is waiting...\n", getpid());
        wait(NULL);

        printf("Parent received an alarm from child process with PID %d.\n", pid);
    }
}

