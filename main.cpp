/*-----------------------------------------------------------------------------#
#-------------------------------main.cpp --------------------------------------#
#-Author: Michael Issa---------------------------------------Red ID: 824099283*/

#define DEFAULT_NUM_REQUESTS 100
#define MAX_NUM_SANDWICHES 8
#define MAX_NUM_REQUESTS 20
#define SCALE_TO_CONVERT_TO_MS 1000

#include <fstream>
#include <iostream>

#include "fooddelivery.h"
#include "broker.h"
#include "producer.h"
#include "consumer.h"
using namespace std;

int main(int argc, char **argv) {

    int n = DEFAULT_NUM_REQUESTS; // Number of default requests
    int a = 0; // Variable factor for DeliveryServiceA
    int b = 0; // Variable factor for DeliveryServiceB
    int p = 0; // Variable factor for Pizza producer
    int s = 0; // Variable factor for Sandwich producer

    int option;
    // Parse command line arguments
    while ((option = getopt(argc, argv, "n:a:b:p:s:")) != -1)
    {
        switch (option)
        {
        case 'n': 
            n = atoi(optarg); // Set number of requests
            break;
        case 'a': 
            a = atoi(optarg) * SCALE_TO_CONVERT_TO_MS; 
            break;
        case 'b': 
            b = atoi(optarg) * SCALE_TO_CONVERT_TO_MS;
            break;
        case 'p':
            p = atoi(optarg) * SCALE_TO_CONVERT_TO_MS;
            break;
        case 's': 
            s = atoi(optarg) * SCALE_TO_CONVERT_TO_MS; 
            break;
        default:
            exit(EXIT_FAILURE); 
        }
    }
    
    Broker broker; // Create broker instance

    // Initialize arrays in broker instance
    for (unsigned i = 0; i < RequestTypeN; i++) {
        broker.inBrokerQueue[i] = 0;
        broker.produced[i] = 0;
    }

    // Initialize consumed array in broker instance
    for (unsigned i = 0; i < RequestTypeN; i++) {
        for (unsigned j = 0; j < ConsumerTypeN; j++) {
            broker.consumed[j][i] = 0;
        }
    }

    // Initialize semaphores in broker instance
    sem_init(&(broker.mutex), 1, 1);
    sem_init(&(broker.itemsAvailable), 1, 0);
    sem_init(&(broker.sandwichAvailable), 1, MAX_NUM_SANDWICHES);
    sem_init(&(broker.bufferSpaceAvailable), 1, MAX_NUM_REQUESTS);
    sem_init(&(broker.start), 1, 0);
    sem_init(&(broker.finish), 1, 0);

    pthread_t pizzaGuy;     // Thread for pizza producer
    pthread_t sandwichGuy;  // Thread for sandwich producer
    pthread_t deliveryThreadA; // Thread for DeliveryServiceA consumer
    pthread_t deliveryThreadB; // Thread for DeliveryServiceB consumer

    // Create producer and consumer instances
    Producer pizzaProducer = createProducer(&broker, Pizza, p);
    Producer sandwichProducer = createProducer(&broker, Sandwich, s);
    Consumer deliveryA = createConsumer(&broker, DeliveryServiceA, a);
    Consumer deliveryB = createConsumer(&broker, DeliveryServiceB, b);

    // Create threads for producers and consumers
    pthread_create(&pizzaGuy, NULL, &produce, &pizzaProducer);
    pthread_create(&sandwichGuy, NULL, &produce, &sandwichProducer);
    pthread_create(&deliveryThreadA, NULL, &consume, &deliveryA);
    pthread_create(&deliveryThreadB, NULL, &consume, &deliveryB);

    // Start producing requests
    for (int i = 0; i < n; i++)
    {
        sem_post(&(broker.start));
    }

    // Wait for all requests to be processed
    for (int i = 0; i < n; i++)
    {
        sem_wait(&(broker.finish));
    }
 
    // Wait for buffer space to be available
    for (int i = 0; i < MAX_NUM_REQUESTS; i++)
    {
        sem_wait(&(broker.bufferSpaceAvailable));
    }

    // Log production history
    log_production_history(broker.produced, broker.consumed);

    return 0;
}
