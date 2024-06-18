/*-----------------------------------------------------------------------------#
#-------------------------------broker.h --------------------------------------#
#-Author: Michael Issa---------------------------------------Red ID: 824099283*/

#ifndef BROKER_H
#define BROKER_H

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "fooddelivery.h"

using namespace std;

/**
 * @brief Represents a broker that manages requests between producers and consumers.
 * 
 */
struct Broker
{   
    queue<RequestType> requests;      // Queue to hold request
    sem_t itemsAvailable;             // Semaphore for available items in the buffer
    sem_t sandwichAvailable;          // Semaphore for available sandwiches in the buffer
    sem_t bufferSpaceAvailable;       // Semaphore for available buffer space
    sem_t start;                      // Semaphore to start processing requests
    sem_t finish;                     // Semaphore to signal request processing completion
    sem_t mutex;                      // Semaphore for mutual exclusion
    unsigned int produced[RequestTypeN];       // Array to hold counts of produced requests
    unsigned int inBrokerQueue[RequestTypeN];  // Array to hold counts of requests in the broker queue
    unsigned int consumed[ConsumerTypeN][RequestTypeN]; // 2D array to hold counts of consumed requests by consumers
};

#endif
