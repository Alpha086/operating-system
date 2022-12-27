#include<iostream>
#include<queue>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

using namespace std;

//Declaring Buffers
queue<int> buffer1;
queue<int> buffer2;
queue<int> buffer3;

//Declaring Semaphores
sem_t empty_1;
sem_t full_1;

sem_t empty_2;
sem_t full_2;

sem_t empty_3;
sem_t full_3;

//Declaring Locks
pthread_mutex_t lock_1;
pthread_mutex_t lock_2;
pthread_mutex_t lock_3;

//Initializing Shared Variable
int count = 0;

//Initializing Semaphores
void init_semaphore()
{
    sem_init(&empty_1,0,5);
    sem_init(&full_1,0,0);
    pthread_mutex_init(&lock_1,0);

    sem_init(&empty_2,0,3);
    sem_init(&full_2,0,0);
    pthread_mutex_init(&lock_2,0);

    sem_init(&empty_3,0,1);
    sem_init(&full_3,0,0);
    pthread_mutex_init(&lock_3,0);

}
void * consumer_waiter(void * arg)
{
    printf("%s\n",(char*)arg);
	for(int i=0;i<=5;i++)
	{

		sem_wait(&full_3);

		pthread_mutex_lock(&lock_3);
		usleep(1);
		int item3 = buffer3.front();
		buffer3.pop();
		printf("waiter has delivered order %d\n",item3);
		pthread_mutex_unlock(&lock_3);

		sem_post(&empty_3);

	}
}


int main()
{
    pthread_t thread2;
    char * message2 = "i am waiter";

    init_semaphore();
    pthread_create(&thread2, NULL, consumer_waiter, (void*)message2 );

    while(1);

    return 0;



}
