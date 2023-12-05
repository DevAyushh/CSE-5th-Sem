#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void main()
{
    int fd1, fd2;
    char s1[100];
    char s2[100];
    char result[100];

    unlink("./myfifo");
    mkfifo("./myfifo", 0666);

    unlink("./result_fifo");
    mkfifo("./result_fifo", 0666);

    printf("Process 1: Enter the first string: ");
    scanf("%s", s1);
    printf("Process 1: Enter the second string: ");
    scanf("%s", s2);
    printf("Process 1: Input sent to process 2.\n");

    fd1 = open("./myfifo", O_WRONLY);
    write(fd1, s1, strlen(s1) + 1);
    sleep(1);
    write(fd1, s2, strlen(s2) + 1);
    close(fd1);

    fd2 = open("./result_fifo", O_RDONLY);
    read(fd2, result, sizeof(result));
    printf("Process 1: Received result from Process 2: %s\n", result);
    close(fd2);
}

