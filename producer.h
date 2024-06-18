/*-----------------------------------------------------------------------------#
#-------------------------------producer.h ------------------------------------#
#-Author: Michael Issa---------------------------------------Red ID: 824099283*/

#ifndef PRODUCER_H
#define PRODUCER_H

#include "fooddelivery.h"
#include "broker.h"
#include "log.h"

/**
 * @brief Represents a producer that creates requests to be processed by the broker.
 * 
 */
struct Producer
{   
    Broker *broker;     
    RequestType type;  
    int sleepTime;       
};

/**
 * @brief Creates a producer instance.
 * 
 * @param broker    Pointer to the broker instance
 * @param type      Type of request the producer creates
 * @param sleepTime Time to sleep between producing requests
 * @return Producer The created producer instance
 */
Producer createProducer(Broker *broker, RequestType type, int sleepTime);

/**
 * @brief The function executed by the producer thread to produce requests.
 * 
 * @param p Pointer to the producer instance
 * @return void* Result of the thread execution
 */
void *produce(void *p);

#endif

