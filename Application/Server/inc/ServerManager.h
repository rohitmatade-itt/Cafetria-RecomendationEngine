#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <string>

#include "ServerSocket.h"
#include "SocketProtocol.h"

class ServerManager {
public:
    ServerManager(int port);
    ~ServerManager();

    void start();
    std::string receiveMessage();
    SocketRequest parseSocketRequest(std::string input);

    void handleClientRequest();

private:
    int port;
    ServerSocket* serverSocket;
    
};

#endif // SERVERMANAGER_H
