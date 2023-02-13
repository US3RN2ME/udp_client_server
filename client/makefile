CC=gcc
SOURCES=./src/main.c ./src/client.c
EXECUTABLE=./build/client

all: 
	$(CC) $(SOURCES) -o $(EXECUTABLE) -lws2_32 -lwsock32
	
run:
	${EXECUTABLE}
