#ifndef MYMALLOC_H_
#define MYMALLOC_H_ 

#include <unistd.h>

//Protótipos
int MyMallocInit(long long unsigned size);

void* MyMalloc(long long unsigned size);

int MyMallocFree(void *ptr);

void MyMallocGerency();

unsigned MyMallocStructSize();

#endif
