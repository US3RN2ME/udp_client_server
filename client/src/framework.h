#ifndef FRAMEWORK_H
#define FRAMEWORK_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define LENGTH 256
#define LOCALHOST "127.0.0.1"
#define DEFAULT_PORT 8080


#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>

#define close_socket(sckt) closesocket(sckt)

typedef SOCKET socket_t;

#define non_blocking(sckt)                              \
DWORD nonBlocking = 1;                                  \
if (ioctlsocket(sckt, FIONBIO, &nonBlocking) != 0) {    \
    printf("Failed to set non-blocking socket: %d", WSAGetLastError());\
    exit(EXIT_FAILURE); }

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define close_socket(sckt) close(sckt)

typedef int socket_t;

#define non_blocking(sckt)                                      \
int nonBlocking = 1;                                            \
if (fcntl(sckt, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {      \
    printf("Failed to set non-blocking socket");                \
    exit(EXIT_FAILURE); }

#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif 

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif 

#endif // !FRAMEWORK_H