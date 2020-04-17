// Q 2. WAP to implement race condition using semaphores.

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
void *fun1(); 	//thread1 function declaration
void *fun2(); 	//thread2 function declaration
int shared=1; 	//shared variable declaration
sem_t s;     //semaphore variable
int main()
{
sem_init(&s,0,1);  	 // initailize semaphore variable
pthread_t thread1,thread2; 		//thread declaration
pthread_create(&thread1,NULL,fun1,NULL); 	//creating and executing thread1
pthread_create(&thread2,NULL,fun2,NULL); 	//creating and executing thread2
pthread_join(thread1,NULL); 			//joining thread1 with main function
pthread_join(thread2,NULL); 	           	//joining thread2 with main function
printf("FINAL VALUE OF SHARED VARIABLE IS %d \n",shared);
}

void *fun1()        //defination of thread1 function
{
int x;	      //local variable declaration
sem_wait(&s);     //executes wait operation on s
x=shared;
x++; 		//increment the value
sleep(1); 	//preemption
shared=x;
sem_post(&s);	 //executes signal operation on s
}
void *fun2()
{
int y;		//local variable declaration
sem_wait(&s);	//executes wait operation on s
y=shared;	
y--; 		//decrement the value
sleep(3); 	//preemption
shared=y;
sem_post(&s);	 //executes signal operation on s
}
