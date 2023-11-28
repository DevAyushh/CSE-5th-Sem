#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int alarm_raised = 0;
int sig = 0;

void raised_alarm_handler(int signum)
{
    alarm_raised = 1;
    sig = signum;
}

int main()
{
    signal(SIGALRM, raised_alarm_handler);
    int pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child process with PID %d and PPID %d is running...\n", getpid(), getppid());
        sleep(5);
        kill(getppid(), SIGALRM);
        printf("Child process sent alarm to parent.\n");
        exit(0); // Child process exits after sending the signal
    }
    else
    {
        printf("Parent process with PID %d is waiting...\n", getpid());

        while (alarm_raised == 0)
        {
            printf("Hello, I am Ayush from the parent process...\n");
            sleep(1);
        }

        printf("Parent received an alarm from child process with PID %d.\n", pid);
        printf("The signal number is: %d\n", sig);
    }

    return 0;
}

