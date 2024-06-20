#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <netinet/in.h>
#include <string>
#include <utility>

#include "SocketProtocol.h"

class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();
    void acceptConnection();
    void sendMessage(int requestType, std::string message);
    std::string receiveMessage();

private:
    int serverSocket;
    int requestSocket;
    struct sockaddr_in socketAddress;
    int socketAddressLength;
    int port;

    void createSocket();
    void bindSocket();
    void listenSocket();
    SocketRequest parseMessage(const std::string& message);
};

#endif // SERVERSOCKET_H
