#include <iostream>
#include <cstring>
#include <unistd.h>

#include "ServerSocket.h"

ServerSocket::ServerSocket(int port) : port(port), socketAddressLength(sizeof(socketAddress)) {
    createSocket();
    bindSocket();
    listenSocket();
}

ServerSocket::~ServerSocket() {
    close(requestSocket);
    close(serverSocket);
}

void ServerSocket::createSocket() {
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::bindSocket() {
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&socketAddress, socketAddressLength) < 0) {
        perror("bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::listenSocket() {
    if (listen(serverSocket, 3) < 0) {
        perror("listen");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::acceptConnection() {
    if ((requestSocket = accept(serverSocket, (struct sockaddr *)&socketAddress, (socklen_t*)&socketAddressLength)) < 0) {
        perror("accept");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::sendMessage(const std::string& message) {
    send(requestSocket, message.c_str(), message.size(), 0);
    std::cout << "Message sent: " << message << std::endl;
}

std::string ServerSocket::receiveMessage() {
    char buffer[1024] = {0};
    int sizeOfBuffer = read(requestSocket, buffer, 1024);
    std::string message(buffer, sizeOfBuffer);
    return message;
}