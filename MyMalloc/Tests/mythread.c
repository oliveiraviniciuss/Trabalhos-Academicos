#include <stdio.h>
#include "mymalloc.h"
#include <pthread.h>
#include <time.h>
 
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{

	if ((unsigned) vargp % 10 == 0)
		vargp++;

    void* chunk = (void*) MyMalloc((unsigned) vargp % 10 *sizeof(char));

    printf("Allocated %d for Thread %u\n", (unsigned) vargp % 10, (unsigned) vargp);

   MyMallocFree(chunk);

    printf("Deallocated %d for Thread %u\n", (unsigned) vargp % 10, (unsigned) vargp);


    return NULL;
}
  
int main()
{

	clock_t start, end;

   pthread_t thread_id [15000];

   MyMallocInit(500000); //1mb

   start = clock();

   for (int i = 0; i < 15000; i ++)
   		pthread_create(&thread_id[i], NULL, myThreadFun, i);

   for (int i = 0; i < 15000; i ++)
   		pthread_join(thread_id[i], NULL);

   	end = clock();

   	printf("TIME: %lf \n\n", (end - start)/(double)CLOCKS_PER_SEC);
   

   MyMallocGerency();
  
   
   return 0;
}