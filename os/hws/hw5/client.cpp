#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MAX_BUF 256
char tmp_buf[MAX_BUF];

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Arguments expected: <server-name> <client-name> <message>";
        return 1;
    }

    int sock_fd;
    if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        std::cerr << "Can't create socket\n";
        return 1;
    }

    sockaddr_un client_address = {0};
    client_address.sun_family = AF_UNIX;
    strcpy(client_address.sun_path, argv[2]);

    if (bind(sock_fd, reinterpret_cast<const sockaddr *>(&client_address),
              sizeof(client_address.sun_family) + strlen(client_address.sun_path)) == -1) {
        close(sock_fd);
        std::cerr << "Can't bind socket to adress\n";
        return 1;
    }

    sockaddr_un server_address = {0};
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, argv[1]);
    if (sendto(sock_fd, argv[3], strlen(argv[3]), 0, reinterpret_cast<const sockaddr *>(&server_address),
               sizeof(server_address.sun_family) + strlen(server_address.sun_path)) == -1) {
        close(sock_fd);
        unlink(client_address.sun_path);
        std::cerr << "Error sending message\n";
        return 1;
    }

    int received_len;
    if ((received_len = recvfrom(sock_fd, tmp_buf, MAX_BUF, 0, NULL, 0)) == -1) {
        close(sock_fd);
        unlink(client_address.sun_path);
        std::cerr << "Error with receiving\n";
        return 1;
    }

    std::cout << "Echo: " << tmp_buf << '\n';
    close(sock_fd);
    unlink(client_address.sun_path);
}