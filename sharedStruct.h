//sharedSturct.h

#include <semaphore.h>
#include <pthread.h>

#ifndef SHAREDSTRUCT_H_
#define SHAREDSTRUCT_H_

struct sharedMemBuff{
sem_t empty;
sem_t full;
int buffer[2];
};

#endif /*SHAREDSTRUCT_H_*/