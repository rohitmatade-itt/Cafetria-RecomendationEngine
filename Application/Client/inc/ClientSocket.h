#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>
#include <netinet/in.h>

class ClientSocket {
public:
    ClientSocket();
    ~ClientSocket();
    void sendMessage(const int& requestType, const std::string& message);
    std::string receiveMessage();

private:
    const char* ipAddress;
    int port;
    int clientSocket;
    struct sockaddr_in serverAddress;

    void createSocket();
    void connectToServer();
};

#endif // CLIENTSOCKET_H
