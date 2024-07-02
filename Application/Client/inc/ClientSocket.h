#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>
#include <netinet/in.h>

class ClientSocket {
public:
    // Deleted copy constructor and assignment operator to prevent copying
    ClientSocket(const ClientSocket&) = delete;
    ClientSocket& operator=(const ClientSocket&) = delete;

    // Public static method to access the singleton instance
    static ClientSocket& getInstance() {
        static ClientSocket instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    void sendMessage(const int& requestType, const std::string& message);
    std::string receiveMessage();

private:
    ClientSocket(); // Constructor is private
    ~ClientSocket(); // Destructor can be private or public

    const char* ipAddress;
    int port;
    int clientSocket;
    struct sockaddr_in serverAddress;

    void createSocket();
    void connectToServer();
};

#endif // CLIENTSOCKET_H