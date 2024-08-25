#ifndef SOCKETPROTOCOL_H
#define SOCKETPROTOCOL_H

#include <string>
#include <utility>

struct SocketRequest {
    int requestType;
    std::string message;
};

#endif // SOCKETPROTOCOL_H
