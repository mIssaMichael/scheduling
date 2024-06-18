# Consumer-Producer Problem

## Overview
Class assignment for simulating a food delivery system using a multi-threaded environment(semaphores and threads). The main components include producers (Pizza and Sandwich makers) and consumers (DeliveryServiceA and DeliveryServiceB) which interact through a broker managing the requests and deliveries.

## Files
main.cpp: Contains the main function to initialize and run the simulation.
fooddelivery.h: Header file containing definitions and structures related to the food delivery system.
broker.h: Header file defining the broker structure and its associated semaphores.
producer.h: Header file defining the producer structure and functions.
consumer.h: Header file defining the consumer structure and functions.

## Compilation
g++ -o fooddelivery main.cpp -lpthread

Options
-n [num]: Number of requests (default is 100)
-a [ms]: Time interval for DeliveryServiceA in milliseconds (default is 0)
-b [ms]: Time interval for DeliveryServiceB in milliseconds (default is 0)
-p [ms]: Time interval for Pizza producer in milliseconds (default is 0)
-s [ms]: Time interval for Sandwich producer in milliseconds (default is 0)

## Example Usage
./fooddelivery -n 50 -a 500 -b 1000 -p 200 -s 300

