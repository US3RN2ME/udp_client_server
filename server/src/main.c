#include "server.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        uint16_t port = atoi(argv[1]);
        if (!port) {
            printf("Bad port");
            return -1;
        }
        run_server(port);
    }
    else {
        run_server(DEFAULT_PORT);
    }

    return 0;
}