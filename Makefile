CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-pthread
SOURCES=main.cpp monitor.cpp thread_wrapper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm *.o main 
