#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <arpa/inet.h>

class ClientSocket {
public:
    ClientSocket(const char* ipAddress, int port);
    ~ClientSocket();
    void sendMessage(const std::string& message);
    std::string receiveMessage();

private:
    int clientSocket;
    struct sockaddr_in serverAddress;
    const char* ipAddress;
    int port;

    void createSocket();
    void connectToServer();
};

#endif // CLIENTSOCKET_H