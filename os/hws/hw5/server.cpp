#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MAX_BUF 256
char tmp_buf[MAX_BUF];

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Arguments expected: <server-name>";
        return 1;
    }

    int sock_fd;
    if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        std::cerr << "Can't create socket\n";
        return 1;
    }

    sockaddr_un server_address = {0};
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, argv[1]);

    if ((bind(sock_fd, reinterpret_cast<const sockaddr *>(&server_address),
              sizeof(server_address.sun_family) + strlen(server_address.sun_path)) == -1)) {
        close(sock_fd);
        std::cerr << "Can't bind socket to adress\n";
        return 1;
    }


    sockaddr_un client_address = {0};
    int client_address_len = sizeof(client_address);
    while (true) {
        int received_len = recvfrom(sock_fd, tmp_buf, MAX_BUF, 0,
                reinterpret_cast<sockaddr *>(&client_address), reinterpret_cast<socklen_t *>(&client_address_len));
        if (received_len == -1) {
            close(sock_fd);
            std::cerr << "Error with receiver\n";
            return 1;
        }
        int sended_len = sendto(sock_fd, tmp_buf, received_len, 0,
                reinterpret_cast<sockaddr *>(&client_address), client_address_len);
        if (sended_len != received_len) {
            close(sock_fd);
            std::cerr << "Error while sending\n";
            return 1;
        }
    }
}