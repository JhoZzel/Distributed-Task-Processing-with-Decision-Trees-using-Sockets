#include <iostream>
#include <cstring> // Para funciones como memset
#include <cstdlib> // Para función exit
#include <unistd.h> // Para función close
#include <arpa/inet.h> // Para estructuras de dirección de red
#include <sys/socket.h> // Para funciones relacionadas con sockets

const std::string END = "END";

void error(const std::string& msg) {
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

void connect(const std::string& host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error("Error creating socket");
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr) <= 0) {
        error("Invalid address or address not supported");
    }

    if (connect(sock, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        error("Connection failed");
    }

    std::cout << "Connected to " << host << ":" << port << std::endl;

    std::string username;
    std::cout << "Type your username: ";
    std::getline(std::cin, username);

    std::string msg;
    std::cout << "Send the message " << END << " to finish" << std::endl;
    while (true) {
        std::cout << "Write a message and press Enter to send it" << std::endl;
        std::getline(std::cin, msg);

        if (msg == END) {
            break;
        }

        msg = "[" + username + "]: " + msg + "\n";

        if (send(sock, msg.c_str(), msg.size(), 0) == -1) {
            error("Failed to send message");
        }

        char buffer[128];
        memset(buffer, 0, sizeof(buffer));
        if (recv(sock, buffer, sizeof(buffer), 0) == -1) {
            error("Error receiving response");
        }

        std::cout << buffer << std::endl;
    }

    close(sock);
    std::cout << "Connection closed" << std::endl;
}

int main() {
    const std::string HOST = "127.0.0.1";
    const int PORT = 8084;
    connect(HOST, PORT);

    return 0;
}
