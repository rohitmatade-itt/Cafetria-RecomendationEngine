#ifndef MOCKCLIENTSOCKET_H
#define MOCKCLIENTSOCKET_H

#include "ClientSocket.h"
#include <gmock/gmock.h>

class ClientSocketMockInterface {
public:
    virtual ~ClientSocketMockInterface() = default;
    virtual void sendMessage(int requestType, const std::string& message) = 0;
    virtual std::string receiveMessage() = 0;
};

class MockClientSocket : public ClientSocketMockInterface {
public:
    MOCK_METHOD(void, sendMessage, (int requestType, const std::string& message), (override));
    MOCK_METHOD(std::string, receiveMessage, (), (override));
};

#endif // MOCKCLIENTSOCKET_H
