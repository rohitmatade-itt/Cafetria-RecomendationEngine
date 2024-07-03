#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <string>

#include "ServerSocket.h"
#include "SocketProtocol.h"

class ServerManager {
public:
    ServerManager(int port);
    ~ServerManager();

    bool start();
    SocketRequest parseSocketRequest(std::string input);
    void acceptConnection();

    std::string handleClientRequest(std::string message);

private:
    int port;
    ServerSocket* serverSocket;
    
};

#endif // SERVERMANAGER_H
