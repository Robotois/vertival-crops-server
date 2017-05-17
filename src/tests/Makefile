CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
LIBS = -l bcm2835 -l rt

OBJECTS = \
	test.o \
	MCP23008.o \
	IOModule.o \
	AccurateTiming.o

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: io.o mcp.o timer.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: test.cpp
	$(CC) $(COMPILE_FLAGS) test.cpp
mcp.o: ../Libraries/MCP23008/MCP23008.cpp ../Libraries/MCP23008/MCP23008.h
	$(CC) $(COMPILE_FLAGS) ../Libraries/MCP23008/MCP23008.cpp
timer.o: ../Libraries/Timer/AccurateTiming.cpp ../Libraries/Timer/AccurateTiming.h
	$(CC) $(COMPILE_FLAGS) ../Libraries/Timer/AccurateTiming.cpp
io.o: ../Modules/IOModule.cpp ../Modules/IOModule.h
	$(CC) $(COMPILE_FLAGS) ../Modules/IOModule.cpp

clean:
	$(RM) $(OBJECTS) runner
