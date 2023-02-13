#include "server.h"

void stop_server(socket_t sock) {
	shutdown(sock, 0);
	close_socket(sock);
#ifdef _WIN32 
	WSACleanup();
#endif
}

void run_server(uint16_t port) {
#ifdef _WIN32
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
		printf("Failed to initialize Winsock : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
#endif
	sock_addr server;
	server.addr.sin_addr.s_addr = INADDR_ANY;
	server.addr.sin_port = htons(port);
	server.addr.sin_family = AF_INET;

	server.sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (server.sock == INVALID_SOCKET) {
		printf("Couldn't create socket : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if (bind(server.sock, (struct sockaddr*)&server.addr, sizeof(server.addr)) == INVALID_SOCKET) {
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	non_blocking(server.sock)

	printf("Server is running on port: %u\n", port);

	server_loop(server.sock);
	stop_server(server.sock);
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


void server_loop(socket_t sock) {
	while (1) {
		sock_addr sa;
		sa.sock = sock;

		char* received = receive_data(&sa);
		if (!received) {
			continue;
		}

		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(sa.addr.sin_addr), ip, INET_ADDRSTRLEN);
		printf("received data from %s: %s\n", ip, received);

		sprintf_s(received, LENGTH, "%s will be found", received);

		send_data(&sa, received);

		free(received);
	}
}