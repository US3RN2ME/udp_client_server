#include "client.h"

void close_connection(socket_t sock) {
    shutdown(sock, 0);
    close_socket(sock);
#ifdef _WIN32 
    WSACleanup();
#endif
}

sock_addr initialize_connection(const char* address, uint16_t port) {
#ifdef _WIN32
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        printf("Failed to initialize Winsock : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
#endif
	sock_addr sa;
    sa.sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sa.sock == INVALID_SOCKET) {
        printf("Couldn't create socket : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    sa.addr.sin_addr.s_addr = INADDR_ANY;
    sa.addr.sin_port = htons(port);
    sa.addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, address, (void*)&sa.addr.sin_addr) <= 0) {
        printf("Bad address\n");
        exit(EXIT_FAILURE);
    }

	non_blocking(sa.sock);

    return sa;
}

int send_data(sock_addr* sa, const char* string) {
	char buffer[LENGTH];
	strcpy_s(buffer, LENGTH, string);

	const int bytes_written = sendto(
		sa->sock, buffer, LENGTH, 0,
		(struct sockaddr*)&sa->addr,
		sizeof(sa->addr)
	);

	if (bytes_written == SOCKET_ERROR) {
		printf("Couldn't send data");
	}
	return bytes_written;
}

char* receive_data(sock_addr* sa) {
	char* buffer = (char*)malloc(LENGTH);

	int len = sizeof(sa->addr);
	const int bytes_read = recvfrom(
		sa->sock, buffer, LENGTH, 0,
		(struct sockaddr*)&sa->addr,
		&len
	);

	if (bytes_read == SOCKET_ERROR) {
		free(buffer);
		return NULL;
	}

	return buffer;
}