#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex1, mutex2;
void *func1(void *args)
{
	int i;
	for(i=1; i<=3; i++)
	{
		sem_wait(&mutex1);
		printf("ba");
		sem_post(&mutex2);
	}
	pthread_exit("NULL");
}

void *func2(void *args)
{
	int i;
	for(i=1; i<=3; i++)
	{
		sem_wait(&mutex2);
		printf("ab");
		sem_post(&mutex1);
	}
	pthread_exit("NULL");
}

void main()
{	
	pthread_t th1,th2;
	sem_init(&mutex1, 0, 1);
	sem_init(&mutex2, 0, 0);

	pthread_create(&th1, NULL, func1, NULL);
	pthread_create(&th2, NULL, func2, NULL);
	
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	printf("\n");
	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
}