#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to pass data to the threads
typedef struct {
    int* array;
    int length;
} ThreadData;

// Function to sort array in ascending order
void* ascendingSort(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->length;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data->array[j] > data->array[j + 1]) {
                // Swap
                int temp = data->array[j];
                data->array[j] = data->array[j + 1];
                data->array[j + 1] = temp;
            }
        }
    }

    // Exit the thread and return the sorted array
    printf("Sending the sorted first half to Main..\n");
    pthread_exit(NULL);
}

// Function to sort array in descending order
void* descendingSort(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->length;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data->array[j] < data->array[j + 1]) {
                // Swap
                int temp = data->array[j];
                data->array[j] = data->array[j + 1];
                data->array[j + 1] = temp;
            }
        }
    }

    // Exit the thread and return the sorted array
    printf("Sending the sorted second half to Main..\n");
    pthread_exit(NULL);
}

int main() {
    int n;

    // Input the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Input the array elements
    int* array = (int*)malloc(n * sizeof(int));
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    // Split the array into two halves
    int mid = n / 2;

    // Create thread data for each thread
    ThreadData thread1Data = { array, mid };
    ThreadData thread2Data = { array + mid, n - mid };

    // Declare thread identifiers
    pthread_t thread1, thread2;

    // Create thread 1 (ascending sort)
    pthread_create(&thread1, NULL, ascendingSort, &thread1Data);

    // Create thread 2 (descending sort)
    pthread_create(&thread2, NULL, descendingSort, &thread2Data);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the sorted arrays
    printf("\nSorted Array (Ascending Order): ");
    for (int i = 0; i < mid; i++) {
        printf("%d ", array[i]);
    }

    printf("\nSorted Array (Descending Order): ");
    for (int i = mid; i < n; i++) {
        printf("%d ", array[i]);
    }

    // Free allocated memory
    free(array);

    return 0;
}
