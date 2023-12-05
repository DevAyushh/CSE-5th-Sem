#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void myHandler(int signum) {
    printf("\nInterrupted.\n");
    printf("Received signal number is %d. Stopping the program.\n", signum);
    exit(0);
}
void main() {

    signal(SIGINT, myHandler);
    printf("Running the program. Press Ctrl+C to stop.\n");
    while (1) {
        printf("Process Running...\n");
        sleep(1); 
    }
}
