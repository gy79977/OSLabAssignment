// Q 1.Write a program to implement the solution of dining philosopher problem.

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define LEFT (num-1) %5
#define RIGHT (num+1)% 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

int state[5];  // array keeping track of everyone's state
int philsph[5] ={0,1,2,3,4};  //one semaphore per philosopher
sem_t mutex;    //semaphore variable	
sem_t S[5];



void test(int num)
{
if (state[num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
{
state[num] =EATING;  //Ok , num can eat if neighbour's are not
sleep(2);		//preemption
printf("Philosopher %d takes fork %d and %d\n", num + 1, LEFT + 1, num + 1); 
printf("Philosopher %d is Eating\n", num + 1); 

sem_post(&S[num]);     //wake up num who is waiting on S[num]
}
}

void pickup(int num)      //take up chops
{
sem_wait(&mutex);
state[num] = HUNGRY;
printf("Philosopher %d is Hungry\n", num + 1); 
test(num);  // try to get yourself into eating state
sem_post(&mutex);
sem_wait(&S[num]);  //block if chops were not aquired this is same as "if (state[num] != EATING ) wait ()
 		//because signal (S[num]) would be executed if state [num]
		// is set to EATING successfully
sleep(1);	//preemption
}

void putdown(int num) 	  //put down chops
{
sem_wait(&mutex);
state[num] = THINKING;
printf("Philosopher %d putting fork %d and %d down\n", num + 1, LEFT + 1, num + 1); 
printf("Philosopher %d is thinking\n", num + 1); 
test(LEFT);  	// test left, signal him if he is waiting
test(RIGHT);  //test right, signal  him if he is waiting
sem_post(&mutex);
}



void* philosopher (void* phnum) 
{
while(1)
{
int* i=phnum;
sleep(1);
pickup(*i);  //pick up chops
sleep(0);
putdown(*i);  //put down chops
}
}



int main() 
{ 
int i; 
pthread_t thread_id[5]; 

// initialize the semaphores 
sem_init(&mutex, 0, 1); 

for (i = 0; i < 5; i++) 

sem_init(&S[i], 0, 0); 

for (i = 0; i < 5; i++) { 

// create philosopher processes 
pthread_create(&thread_id[i], NULL, 
               philosopher, &philsph[i]); 

printf("Philosopher %d is thinking\n", i + 1); 
} 

for (i = 0; i < 5; i++) 
pthread_join(thread_id[i], NULL); 
} 



