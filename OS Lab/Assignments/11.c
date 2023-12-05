#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("/tmp", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    char *shared_memory = shmat(shm_id, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Enter a string: ");
    fgets(shared_memory, SHM_SIZE, stdin);

    int child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) { // Child process (P2)
        int is_palindrome = 1;
        int len = strlen(shared_memory) - 1;

        for (int i = 0; i < len / 2; i++) {
            if (shared_memory[i] != shared_memory[len - i - 1]) {
                is_palindrome = 0;
                break;
            }
        }

        shmdt(shared_memory);
        exit(is_palindrome); // Exit with 0 for not palindrome and 1 for palindrome
    } else { // Parent process (P1)
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int is_palindrome = WEXITSTATUS(status);
            if (is_palindrome) {
                printf("Palindrome\n");
            } else {
                printf("Not Palindrome\n");
            }
        }

        shmctl(shm_id, IPC_RMID, NULL);
    }

    return 0;
}

