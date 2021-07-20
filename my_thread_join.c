/**************************************************************************************
 *1. A join is performed when one wants to wait for a thread to finish. A thread calling 
 *   routine may launch multiple threads then wait for them to finish to get the results. 
 *   One wait for the completion of the threads with a join.
 *
 *2. Mutex-
 *   Mutual exclusion lock: Block access to variables by other threads. This enforces exclusive 
 *   access by a thread to a variable or set of variables. 
 * 
 *   Mutexes are used to prevent data inconsistencies due to race conditions. A race condition 
 *   often occurs when two or more threads need to perform operations on the same memory area,
 *   but the results of computations depends on the order in which these operations are performed.
 *   Mutexes are used for serializing shared resources. Anytime a global resource is accessed by 
 *   more than one thread the resource should have a Mutex associated with it. One can apply a mutex
 *   to protect a segment of memory ("critical region") from other threads. Mutexes can be applied 
 *   only to threads in a single process and do not work between processes as do semaphores.
 *
 *   When a mutex lock is attempted against a mutex which is held by another thread, the 
 *   thread is blocked until the mutex is unlocked. When a thread terminates, the mutex 
 *   does not unless explicitly unlocked. Nothing happens by default.
 *
 *   Note - In function thread_function(), if we comment pthread_mutex_lock() and 
 *   pthread_mutex_unlock(), then share variable "counter" will have race condition. And 
 *   value of "counter" variable may become 9 or other, ideally it should be 10.
 *   Source - https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
 **************************************************************************************/

#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10
void *thread_function(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main()
{
   pthread_t thread_id[NTHREADS];
   int i, j;

   for(i=0; i < NTHREADS; i++)
   {
      pthread_create( &thread_id[i], NULL, thread_function, NULL );
   }

   for(j=0; j < NTHREADS; j++)
   {
      pthread_join( thread_id[j], NULL); 
   }
  
   /* Now that all threads are complete I can print the final result.     */
   /* Without the join I could be printing a value before all the threads */
   /* have been completed.                                                */

   printf("Final counter value: %d\n", counter);

   return 0;
}

void *thread_function(void *dummyPtr)
{
   printf("Thread number %ld\n", pthread_self());
   pthread_mutex_lock( &mutex1 );
   usleep(250000);
   counter++;
   pthread_mutex_unlock( &mutex1 );
}
