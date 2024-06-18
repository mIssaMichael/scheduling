/*-----------------------------------------------------------------------------#
#-------------------------------consumer.cpp ----------------------------------#
#-Author: Michael Issa---------------------------------------Red ID: 824099283*/

#include "consumer.h"

Consumer createConsumer(Broker *broker, ConsumerType type, int sleepTime) {
    Consumer consumer;
    consumer.type = type;          
    consumer.broker = broker;     
    consumer.sleepTime = sleepTime; 
    return consumer;              
}


void *consume(void *c) {
    
    Consumer *consumer = (Consumer *)c; // Cast void pointer to Consumer pointer
    RequestType requestType;

    while (true)
    {
    
        sem_wait(&(consumer->broker->itemsAvailable)); // Wait for items to be available in buffer
        sem_wait(&(consumer->broker->mutex)); // Acquire mutex lock for critical section

        // Enter critical section
        requestType = consumer->broker->requests.front(); // Get the front request from the queue
        consumer->broker->requests.pop(); // Remove the front request from the queue
        consumer->broker->consumed[consumer->type][requestType]++; // Increment consumed count for the consumer type and request type
        consumer->broker->inBrokerQueue[requestType]--; // Decrement count in broker queue for the request type
        // Exit critical section
        
        log_removed_request(consumer->type, requestType, consumer->broker->consumed[consumer->type], consumer->broker->inBrokerQueue); // Log the removed request
        
        sem_post(&(consumer->broker->mutex)); // Release mutex lock
        sem_post(&(consumer->broker->bufferSpaceAvailable)); // Signal availability of buffer space

        if (requestType == Sandwich) {
            sem_post(&(consumer->broker->sandwichAvailable)); // Signal availability of sandwich
        }

        usleep(consumer->sleepTime); // Sleep for specified time
    }
}
