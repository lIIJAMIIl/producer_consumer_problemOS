# producer_consumer_problemOS
Illustrating the producer/consumer problem using shared memory for IPC
Project Title(s):
        producer.c
        consumer.c
        sharedStruct.h

Project Description:
        This project illustrates execution of two communicating processes using shared
memory. The producer process and comsumer processes use semaphores to signal when they
are in the critical section. Producer writes to buffer[], a shared memory space. Consumer
reads from buffer[]. I ran into issues attemping to use a mutex lock, and unfortunately
could not get the processes to run when implementing a mutex lock. In the future, I would
like to try a similar approach to the producer consumer problem using multiple threads
for the producer and consumer processes.

Running producer.c and consumer.c:
        Compile each:
                gcc producer.c -pthread -lrt -o producer
                gcc consumer.c -pthread -lrt -o consumer
        Execute:
                ./producer & ./consumer &


