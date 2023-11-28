#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *customThread(void *input)
{
int n=*((int *)input);   //int *n = int *input; int m = *n;
int i,c=1;
if(n==1)
{
printf("%d is neither prime nor composite\n",n);
pthread_exit(NULL);
}

for(i=2;i<=n;i++)
{
if(n%i==0) 
c+=1;
}
if(c==2) 
{
	printf("%d is prime\n",n);
}
else 
    printf("%d is not prime\n",n);
pthread_exit(NULL);
}

int main() {
    pthread_t t;
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    pthread_create(&t, NULL, customThread, &n);
    pthread_join(t, NULL);

    return 0;
}

