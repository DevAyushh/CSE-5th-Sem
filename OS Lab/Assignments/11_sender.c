#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHARED_MEMORY_KEY 1234

int main() {
    void *shared_memory;
    char buff[1024];
    int shmid = shmget((key_t)SHARED_MEMORY_KEY, 1024, 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, NULL, 0);

    printf("Enter the string to be passed: ");
    scanf("%[^\n]s", buff);
    strcpy(shared_memory, buff);
    printf("Data stored in shared memory: %s\n", (char *)shared_memory);

    return 0;
}