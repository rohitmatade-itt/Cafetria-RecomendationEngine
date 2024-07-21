#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>
#include <netinet/in.h>

class ClientSocket {
public:
    ClientSocket(const ClientSocket&) = delete;
    ClientSocket& operator=(const ClientSocket&) = delete;

    static ClientSocket& getInstance() {
        static ClientSocket instance;
        return instance;
    }

    void sendMessage(const int& requestType, const std::string& message);
    std::string receiveMessage();

private:
    ClientSocket();
    ~ClientSocket();

    const char* ipAddress;
    int port;
    int clientSocket;
    struct sockaddr_in serverAddress;

    void createSocket();
    void connectToServer();
};

#endif // CLIENTSOCKET_H