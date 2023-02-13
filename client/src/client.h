#ifndef CLIENT_H
#define CLIENT_H
#include "framework.h"

typedef
struct SOCK_ADDR {
	socket_t sock;
	SOCKADDR_IN addr;
} sock_addr;

////////////////////////////////////////////
/// \brief closes the connection
////////////////////////////////////////////
void close_connection(socket_t sock);

////////////////////////////////////////////
/// \brief establishes a connection in
/// a local network using the specefied 
/// address and port
////////////////////////////////////////////
sock_addr initialize_connection(const char* address, uint16_t port);

////////////////////////////////////////////
/// \brief receives data from the specefied 
/// socket
////////////////////////////////////////////
char* receive_data(sock_addr* sock);

////////////////////////////////////////////
/// \brief sends data to the specefied 
/// socket
////////////////////////////////////////////
int send_data(sock_addr* sock, const char* string);

#endif // !CLIENT_H