// AIM: To simulate the Producer-Consumer Problem using multiple threads and simple array
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define buffer_size 5
sem_t mutex;
sem_t empty;
sem_t full;
int buffer[buffer_size];
int in = 0;
int out = 0;
int shared_val = 0;

void custom_handler(int signum) {
    printf("\n\nInterrupted by signal %d\n\n", signum);
    sem_post(&full);  // Release a resource in case a consumer is waiting
    sem_post(&empty);  // Release a resource in case a producer is waiting
    exit(0);
}

void *producer(void *input) {
    int item;
    signal(SIGINT,custom_handler);
    
    while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);
        item = shared_val;
        printf("Producer : Adding %d to the buffer\n", item);
        
        if ((in + 1) % buffer_size == out) {
            printf("Buffer overflow! Exiting...\n");
            exit(1);
        }

        buffer[in] = item;
        in = (in + 1) % buffer_size;
        sleep(1);
        sem_post(&mutex);
        shared_val += 1;
        sleep(1);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *input) {
    int item;
    struct sigaction sa;
    sa.sa_handler = custom_handler;
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("Consumer : Read from buffer -> %d\n", item);
        
        if (in == out) {
            printf("Buffer underflow! Exiting...\n");
            exit(1);
        }

        out = (out + 1) % buffer_size;
        sleep(1);
        sem_post(&mutex);
        sleep(1);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    sem_init(&mutex, 0, 1); // Initially unlocked
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    
    printf("Press Ctrl+C to exit...\n");
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    
    exit(0);
}

