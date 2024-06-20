#ifndef SOCKETPROTOCOL_H
#define SOCKETPROTOCOL_H

#include <string>
#include <utility>

struct SocketRequest {
    int requestType;
    std::string message;
};

class SocketProtocol {
public:
    static std::string serialise(const SocketRequest& message);
    static SocketRequest deserialise(const std::string& message);
};

#endif // SOCKETPROTOCOL_H
