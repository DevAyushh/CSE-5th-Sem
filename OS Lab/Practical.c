#include<stdio.h>
#include<unistd.h>
void main()
{
    int p;
    p=fork();
    if(p > 0)
    {
        printf("\nParent process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(15);
        printf("Parent gets the news\n");
	    wait(8);
    }
    else if (p == 0)
    { 
	printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(7);
        printf("Now the child process is killed and it becomes a zombie process\n");
    }
    else
    	printf("Error!");
}



#include<stdio.h>
#include<unistd.h>
# define maxsize 100
void main()
{
    int pid;
    int pfd[2];
    int ret=pipe(pfd);
    char msg[maxsize];
    char msg_rev[maxsize+1];
    pid=fork();
    if(pid==0)
    {
        close(pfd[0]);
        printf("Now in child process, Enter the message\n");
        scanf("%99[^\n]",msg);
        write(pfd[1],msg,sizeof(msg));
        close(pfd[1]);
    }
    else
    {
        close(pfd[1]);
        read(pfd[0],msg_rev,sizeof(msg));
        printf("The message received in parent process is: %s\n",msg_rev);
        close(pfd[0]);
    }
}



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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void main()
{
    int fd, fd_result;
    char s1[100];
    char s2[100];
    char result[100];

    printf("Process 2: Waiting for input\n");

    fd = open("./myfifo", O_RDONLY);
    read(fd, s1, sizeof(s1));
    sleep(1);
    read(fd, s2, sizeof(s2));
    close(fd);

    if (strcmp(s1, s2) == 0)
    {
        strcpy(result, "SAME");
    }
    else
    {
        strcpy(result, "NOT SAME");
    }

    fd_result = open("./result_fifo", O_WRONLY);
    write(fd_result, result, strlen(result) + 1);
    close(fd_result);

    printf("Process 2: Result sent to Process 1.\n");
}




#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void myHandler(int signum) {
    printf("\nInterrupted.\n");
    printf("Received signal number is %d. Stopping the program.\n", signum);
    exit(0);
}
int main() {

    signal(SIGINT, myHandler);
    printf("Running the program. Press Ctrl+C to stop.\n");
    while (1) {
        printf("Process Running...\n");
        sleep(1); 
    }
    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int alarm_raised = 0;
int sig = 0;

void raised_alarm_handler(int signum)
{
    alarm_raised = 1;
    sig = signum;
}

int main()
{
    signal(SIGALRM, raised_alarm_handler);
    int pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child process with PID %d and PPID %d is running...\n", getpid(), getppid());
        sleep(5);
        kill(getppid(), SIGALRM);
        printf("Child process sent alarm to parent.\n");
        exit(0); // Child process exits after sending the signal
    }
    else
    {
        printf("Parent process with PID %d is waiting...\n", getpid());

        while (alarm_raised == 0)
        {
            printf("Hello, I am Ayush from the parent process...\n");
            sleep(1);
        }

        printf("Parent received an alarm from child process with PID %d.\n", pid);
        printf("The signal number is: %d\n", sig);
    }

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

int received = 0;

void leap(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        printf("%d is a Leap Year.\n", year);
    else
        printf("%d is not a Leap Year.\n", year);
}

void custom_handler(int signum) {
    received = 1;
}

int main() {
    signal(SIGCHLD, custom_handler);
    int pid, year;

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) { // Child Process
        printf("Child process with PID %d and PPID %d started...\n", getpid(), getppid());
        while (1) {
            pause();
            if (received == 1) {
                printf("Child Process %d: Enter a year to check for leap year: ", getpid());
                scanf("%d", &year);
                leap(year);
                received = 0;
            }
        }
    } else { // Parent Process
        printf("Parent process with PID %d started...\n", getpid());
        int i = 1;
        while (i == 1) {
            sleep(5);
            printf("Enter 1 to continue or 0 to exit: ");
            scanf("%d", &i);
            if (i == 1) {
                printf("Parent sending a signal to child with PID %d...\n", pid);
                kill(pid, SIGCHLD);
            }
        }
    }
    return 0;
}




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
}



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
    
    sem_init(&mutex, 0, 1);
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
