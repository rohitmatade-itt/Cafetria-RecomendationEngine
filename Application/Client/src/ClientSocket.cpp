#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include "ClientSocket.h"

ClientSocket::ClientSocket() {
    this->ipAddress = "127.0.0.1";
    this->port = 8089;
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
    serverAddress.sin_port = htons(8089);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ClientSocket::sendMessage(const int& requestType, const std::string& message) {
    std::string fullMessage = std::to_string(requestType) + "\t" + message;
    if (send(clientSocket, fullMessage.c_str(), fullMessage.size(), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
    } else {
    }
}

std::string ClientSocket::receiveMessage() {
    char buffer[1024] = {0};
    ssize_t sizeOfBuffer = read(clientSocket, buffer, 1024);
    if (sizeOfBuffer < 0) {
        std::cerr << "Receive failed" << std::endl;
        return "";
    }
    std::string message(buffer, static_cast<size_t>(sizeOfBuffer));
    return message;
}
