/*-----------------------------------------------------------------------------#
#-------------------------------consumer.h ------------------------------------#
#-Author: Michael Issa---------------------------------------Red ID: 824099283*/

#ifndef CONSUMER_H
#define CONSUMER_H

#include "fooddelivery.h"
#include "broker.h"
#include "log.h"

/**
 * @brief Represents a consumer that processes requests from the broker.
 * 
 */
struct Consumer
{   
    Broker *broker;       // Pointer to the broker instance
    ConsumerType type;    // Type of consumer
    int sleepTime;        // Time to sleep between consuming requests
};

/**
 * @brief Creates a consumer instance.
 * 
 * @param broker    Pointer to the broker instance
 * @param type      Type of consumer
 * @param sleepTime Time to sleep between consuming requests
 * @return Consumer The created consumer instance
 */
Consumer createConsumer(Broker *broker, ConsumerType type, int sleepTime);

/**
 * @brief The function executed by the consumer thread to consume requests.
 * 
 * @param c Pointer to the consumer instance
 * @return void* Result of the thread execution
 */
void *consume(void *c);

#endif
