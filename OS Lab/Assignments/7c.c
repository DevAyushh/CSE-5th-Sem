#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

int received = 0;

void leap(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        printf("%d is a Leap Year.\n", year);
    else
        printf("%d is not a Leap Year.\n", year);
}

void custom_handler(int signum) {
    received = 1;
}

int main() {
    signal(SIGCHLD, custom_handler);
    int pid, year;

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(1);
    }

    else if (pid == 0) { // Child Process
        printf("Child process with PID %d and PPID %d started...\n", getpid(), getppid());
        while (1) {
            pause();
            if (received == 1) {
                printf("Child Process %d: Enter a year to check for leap year: ", getpid());
                scanf("%d", &year); 
                leap(year);
                received = 0;
            }
        }
    } else { // Parent Process
        printf("Parent process with PID %d started...\n", getpid());
        int i = 1;
        while (i == 1) {
            sleep(5);
            printf("Enter 1 to continue or 0 to exit: ");
            scanf("%d", &i);
            if (i == 1) {
                printf("Parent sending a signal to child with PID %d...\n", pid);
                kill(pid, SIGCHLD);
            }
        }
    }
    return 0;
}

