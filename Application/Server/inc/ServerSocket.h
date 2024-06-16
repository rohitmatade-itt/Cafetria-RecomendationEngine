#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <arpa/inet.h>

class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();
    void acceptConnection();
    void sendMessage(const std::string& message);
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
};

#endif // SERVERSOCKET_H