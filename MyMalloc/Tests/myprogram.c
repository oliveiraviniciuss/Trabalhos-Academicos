#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int	main(int argc, char const *argv[])
{

	printf("25000 Allocations of 10 bytes each\n\n");
	
	MyMallocInit(1000000); //1mb

	clock_t start, end;

	void* addresses [25000];

	start = clock();

	for (int i = 0; i < 25000; i ++)
	{
		addresses[i] = (void*) MyMalloc(10*sizeof(char));
	}

	end = clock();

	printf("TIME: %lf\n\n", (end-start)/(double) CLOCKS_PER_SEC);



	MyMallocGerency();

	return 0;
}