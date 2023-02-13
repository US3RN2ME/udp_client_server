CC=gcc
SOURCES=./src/main.c ./src/server.c
EXECUTABLE=./build/server

all: 
	$(CC) $(SOURCES) -o $(EXECUTABLE) -lws2_32 -lwsock32
	
run:
	${EXECUTABLE}
