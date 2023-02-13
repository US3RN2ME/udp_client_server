#include "client.h"

int main(int argc, char* argv[]) {
	sock_addr sa;
	if(argc == 3) {
		const char* address = argv[1];
		const int port = atoi(argv[2]);
		if (!port) {
			printf("Bad port");
			return -1;
		}
		sa = initialize_connection(address, port);
	}
	else {
		sa = initialize_connection(LOCALHOST, DEFAULT_PORT);
	}

	char string[LENGTH];
	printf("Enter string to send ->");
	scanf_s("%s", string);

	int sent = send_data(&sa, string);
	if (sent != INVALID_SOCKET) {
		char* received = receive_data(&sa);
		if (received) {
			printf("size: %d bytes\n%s\n", strlen(received), received);
			free(received);
		}
	}

	close_connection(sa.sock);
	_getch();
	return 0;
}