#include<stdio.h>
#include<pthread.h>

void *sum(void *arg)
{
	int n = *((int*)arg);
	int sum = n*(n+1)/2;
	
	printf("Sum: %d\n", sum);
	
	pthread_exit(NULL);
}	

void main(){
	int N;
	printf("Enter a number : ");
	scanf("%d", &N);
	pthread_t th1;
	
	pthread_create(&th1, NULL, sum, (void *)&N);
	pthread_join(th1, NULL);
}