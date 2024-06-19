#include <iostream>
#include <sstream>
#include <stdexcept>
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
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::bindSocket() {
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&socketAddress, socketAddressLength) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::listenSocket() {
    if (listen(serverSocket, 3) < 0) {
        perror("Listen");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::acceptConnection() {
    if ((requestSocket = accept(serverSocket, (struct sockaddr *)&socketAddress, (socklen_t*)&socketAddressLength)) < 0) {
        perror("Accept");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    std::cout << "Connection accepted" << std::endl;
}

void ServerSocket::sendMessage(int requestType, std::string message) {
    std::string fullMessage = std::to_string(requestType) + "\t" + message;
    std::cout << "Sending message: " << fullMessage << std::endl;
    if (send(requestSocket, fullMessage.c_str(), fullMessage.size(), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
    } else {
        std::cout << "Message sent: " << fullMessage << std::endl;
    }
}

std::string ServerSocket::receiveMessage() {
    char buffer[1024] = {0};
    ssize_t sizeOfBuffer = recv(requestSocket, buffer, 1024, 0);
    if (sizeOfBuffer < 0) {
        std::cerr << "Receive failed" << std::endl;
        return "";
    } else if (sizeOfBuffer == 0) {
        std::cout << "Client disconnected" << std::endl;
        return "";
    }
    std::string message(buffer, static_cast<size_t>(sizeOfBuffer));
    std::cout << "Message received: " << message << std::endl;
    return message;
}

SocketRequest ServerSocket::parseMessage(const std::string& message) {
    std::istringstream iss(message);
    std::string requestTypeStr;
    std::getline(iss, requestTypeStr, '\t');

    int requestType;
    try {
        requestType = std::stoi(requestTypeStr);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid request type: " << requestTypeStr << std::endl;
        throw;
    }

    std::string actualMessage;
    std::getline(iss, actualMessage);

    return {requestType, actualMessage};
}


// void ServerSocket::handleMessage(const std::string& message) {
//     try {
//         SocketRequest request = parseMessage(message);
//         std::cout << "Parsed request type: " << request.requestType << ", message: " << request.message << std::endl;
//         // Handle the message based on request type
//     } catch (const std::invalid_argument& e) {
//         std::cerr << "Failed to handle message: " << e.what() << std::endl;
//     }
// }

// void ServerSocket::receiveAndHandleMessages() {
//     while (true) {
//         std::string message = receiveMessage();
//         if (message.empty()) {
//             std::cerr << "Empty message received. Closing connection." << std::endl;
//             break;
//         }
//         handleMessage(message);

        
//     }
// }
