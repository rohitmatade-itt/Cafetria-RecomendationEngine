#include <iostream>
#include <cstring>
#include <unistd.h>

#include "ClientSocket.h"

ClientSocket::ClientSocket(const char* ipAddress, int port) : ipAddress(ipAddress), port(port) {
    createSocket();
    connectToServer();
}

ClientSocket::~ClientSocket() {
    close(clientSocket);
}

void ClientSocket::createSocket() {
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ClientSocket::connectToServer() {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress, &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ClientSocket::sendMessage(const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
    std::cout << "Message sent: " << message << std::endl;
}

std::string ClientSocket::receiveMessage() {
    char buffer[1024] = {0};
    int sizeOfBuffer = read(clientSocket, buffer, 1024);
    std::string message(buffer, sizeOfBuffer);
    return message;
}
