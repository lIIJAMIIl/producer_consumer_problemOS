//Josh Romisher
//10_29_22
//producer_consumer problem 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <time.h>
#include <semaphore.h>
#include "sharedStruct.h"




int main(int argc, char* argv[]){
    /*seeding rand*/
    srand(time(NULL));
    /*Size and name of shared memory object*/
    const char *name = "OS";

    /*Shared memory file descriptor,shMemSegment, and tablePtr of type struct sharedMemBuff*/
    int shMemSegment;
    struct sharedMemBuff* tablePtr;

        /*Creating shared memory object with shm_open(), configuring size*/
        shMemSegment = shm_open(name, O_CREAT |O_RDWR, 0666);
        ftruncate(shMemSegment, sizeof(struct sharedMemBuff));

        /*Mapping the shared memory object, initializing shared memory pointer*/
        tablePtr = mmap(0, sizeof(struct sharedMemBuff), PROT_READ|PROT_WRITE, MAP_SHARED, shMemSegment, 0);

    /*initializing semaphores*/
    sem_init(&tablePtr->empty, 1, 2);
    sem_init(&tablePtr->full, 1, 0);
    
    /*producer routine*/
    int count = 0;
    do{
    printf("Producer Started\n");
    sem_wait(&tablePtr->empty);
    for(int i = 0; i < 2; ++i){
        tablePtr->buffer[i] = (rand() % 100);
        printf("Producer added %d to the table\n", tablePtr->buffer[i]);       
    }
    sem_post(&tablePtr->full);
    ++count;
    sleep(1);
    }while(count < 6);

    return 0;
}