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
    SocketRequest parseSocketRequest(std::string input);

    std::string handleClientRequest(std::string message);

private:
    int port;
    ServerSocket* serverSocket;
    
};

#endif // SERVERMANAGER_H
