#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void main()
{
    int fd, fd_result;
    char s1[100];
    char s2[100];
    char result[100];

    printf("Process 2: Waiting for input\n");

    fd = open("./myfifo", O_RDONLY);
    read(fd, s1, sizeof(s1));
    sleep(1);
    read(fd, s2, sizeof(s2));
    close(fd);

    if (strcmp(s1, s2) == 0)
    {
        strcpy(result, "SAME");
    }
    else
    {
        strcpy(result, "NOT SAME");
    }

    fd_result = open("./result_fifo", O_WRONLY);
    write(fd_result, result, strlen(result) + 1);
    close(fd_result);

    printf("Process 2: Result sent to Process 1.\n");
}

