CXX=g++

CXXFLAGS=-std=c++11 -Wall -g3 -c

OBJS = log.o main.o consumer.o producer.o

PROGRAM = fooddelivery

$(PROGRAM) : $(OBJS)
	$(CXX) -pthread -o $(PROGRAM) $^

log.o : fooddelivery.h log.h log.cpp 
	$(CXX) $(CXXFLAGS) log.cpp 

main.o : log.o consumer.h consumer.cpp producer.h producer.cpp broker.h fooddelivery.h main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

consumer.o : consumer.h consumer.cpp
	$(CXX) $(CXXFLAGS) consumer.cpp 

producer.o : producer.h producer.cpp
	$(CXX) $(CXXFLAGS) producer.cpp 


clean :
	rm -f *.o $(PROGRAM)
