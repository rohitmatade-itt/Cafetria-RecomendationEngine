#include <iostream>

#include "ServerSocket.h"

int main() {
    ServerSocket server(8080);
    server.acceptConnection();
    std::cout << server.receiveMessage() << std::endl;
    return 0;
    
}
