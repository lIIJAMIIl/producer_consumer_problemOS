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
    /*Size and name of shared memory object*/
    const char *name = "OS";

    /*Shared memory file descriptor,shMemSegment*/
    int shMemSegment;
    struct sharedMemBuff* tablePtr;

        /*Creating shared memory object with shm_open(), configuring size*/
        shMemSegment = shm_open(name, O_RDWR, 0);
        if(shMemSegment == -1){
            printf("error");
            exit(1);
        }
        /*Mapping the shared memory object, initializing shared memory pointer*/
        tablePtr = mmap(0, sizeof(struct sharedMemBuff), PROT_READ|PROT_WRITE, MAP_SHARED, shMemSegment, 0);
        if(tablePtr == MAP_FAILED){
            printf("error");
            exit(1);
        }

    /*consumer routine*/
    int count =0;
    do{
    printf("Consumer Started\n");
    sleep(1);
    sem_wait(&tablePtr->full);
    for(int i = 0; i < 2; ++i){
        printf("Consumer removed %d from the table\n", tablePtr->buffer[i]);
    }
    sem_post(&tablePtr->empty);
    ++count;
    }while(count < 6);

    return 0;
}