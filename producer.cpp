/*-----------------------------------------------------------------------------#
#-------------------------------producer.h ------------------------------------#
#-Author: Michael Issa---------------------------------------Red ID: 824099283*/
#include "producer.h"

Producer createProducer(Broker *broker, RequestType type, int sleepTime) {
    Producer producer;
    producer.type = type;        
    producer.broker = broker;    
    producer.sleepTime = sleepTime; 
    return producer;             
}

void *produce(void *p)
{
   
    Producer *producer = (Producer *)p; // Cast void pointer to Producer pointer

    while (true)
    {
        sem_wait(&(producer->broker->start)); // Wait for start signal
        usleep(producer->sleepTime); // Sleep for specified time

        if (producer->type == Sandwich)
        {
            sem_wait(&(producer->broker->sandwichAvailable)); // Wait for sandwich availability
        }

        sem_wait(&(producer->broker->bufferSpaceAvailable)); // Wait for buffer space availability
        sem_wait(&(producer->broker->mutex)); // Acquire mutex lock for critical section

        // Enter critical section
        producer->broker->requests.push(producer->type); // Add request to broker queue
        producer->broker->produced[producer->type]++; // Increment produced count for the request type
        producer->broker->inBrokerQueue[producer->type]++; // Increment count in broker queue for the request type
        // Exit critical section
        log_added_request(producer->type, producer->broker->produced, producer->broker->inBrokerQueue); // Log the added request
        
       
        sem_post(&(producer->broker->mutex)); // Release mutex lock
        sem_post(&(producer->broker->itemsAvailable)); // Signal availability of items in the buffer
        sem_post(&(producer->broker->finish)); // Signal finish
    }
    
}
