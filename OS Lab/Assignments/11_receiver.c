#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <string.h>

#define SHARED_MEMORY_KEY 1234

bool isPalindrome(char *str, int n);

int main() {
    char *str;
    void *shared_memory;
    int shmid = shmget((key_t)SHARED_MEMORY_KEY, 1024, 0666);
    shared_memory = shmat(shmid, NULL, 0);
    str = (char *)shared_memory;

    printf("The string received is: %s\n", str);

    if (isPalindrome(str, strlen(str)))
        printf("%s is a Palindrome.\n", str);
    else
        printf("%s is not a Palindrome.\n", str);

    return 0;
}

bool isPalindrome(char *str, int n) {
    int i;
    for (i = 0; i < n / 2; i++)
        if (str[i] != str[n - i - 1])
            return false;
    return true;
}