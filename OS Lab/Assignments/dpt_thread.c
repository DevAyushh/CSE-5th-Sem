#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>

#define CNT 5

sem_t chopstick[CNT];

void *philosopher(void *input)
{
	int count = *((int *)input);
	int left_chopstick = count;
	int right_chopstick = (count + 1) % CNT;

	printf("\nPhilosopher %d wants to eat, therefore he would need chopsticks %d and %d.\n", count, left_chopstick, right_chopstick);

	printf("Philosopher %d tries to pick up left chopstick, i.e., chopstick %d.\n", count, left_chopstick);
	sem_wait(&chopstick[left_chopstick]);
	printf("Philosopher %d picks up the left chopstick %d\n", count, left_chopstick);

	printf("Philosopher %d tries to pick up the right chopstick, i.e., chopstick %d.\n", count, right_chopstick);
	sem_wait(&chopstick[right_chopstick]);
	printf("Philosopher %d picks up the right chopstick %d\n", count, right_chopstick);

	printf("Philosopher %d is eating\n", count);
	sleep(2);
	printf("Philosopher %d finished eating\n", count);

	sem_post(&chopstick[right_chopstick]);
	printf("Philosopher %d leaves the right chopstick %d\n", count, right_chopstick);

	sem_post(&chopstick[left_chopstick]);
	printf("Philosopher %d leaves the left chopstick %d\n", count, left_chopstick);

	pthread_exit(NULL);
}

void custom_handler(int signum)
{
	int i;
	for (i = 0; i < CNT; i++)
		sem_destroy(&chopstick[i]);
	exit(0);
}

void main()
{
	int i;
	signal(SIGINT, custom_handler);
	pthread_t t[CNT];
	int n[CNT];

	for (i = 0; i < CNT; i++)
		sem_init(&chopstick[i], 0, 1);

	for (i = 0; i < CNT; i++)
	{
		n[i] = i;
		pthread_create(&t[i], NULL, philosopher, (void *)&n[i]);
	}

	for (i = 0; i < CNT; i++)
	{
		pthread_join(t[i], NULL);
		sleep(1);
		printf("\n");
	}
}
