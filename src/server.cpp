#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

Server::Server(int port) {
    this->port = port;
    this->server_fd = 0;
}

Server::~Server() {
    closeServer();
}

void Server::initServer() {
    struct sockaddr_in address;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server initialized on port " << port << std::endl;
}


void Server::waitForConnection() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    std::cout << "Waiting for connections..." << std::endl;

    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection established" << std::endl;
}

void Server::sendData(const char* data) {
    size_t dataLength = strlen(data);
    send(new_socket, &dataLength, sizeof(dataLength), 0); // Send the size of data first
    send(new_socket, data, dataLength, 0); // Then send the data
    std::cout << "Data sent: " << data << std::endl;
}

char* Server::receiveData() {
    size_t bufferSize;
    read(new_socket, &bufferSize, sizeof(bufferSize)); // Read the size of data first

    char *buffer = new char[bufferSize + 1]; // Allocate buffer based on the size received
    read(new_socket, buffer, bufferSize);
    buffer[bufferSize] = '\0'; // Null-terminate the string

    std::cout << "Data received: " << buffer << std::endl;
    return buffer;
}

void Server::closeServer() {
    close(new_socket);
    close(server_fd);
    std::cout << "Server closed" << std::endl;
}

