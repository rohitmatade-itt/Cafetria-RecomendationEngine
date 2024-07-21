#include <iostream>
#include <thread>
#include "ServerManager.h"

int main() {
    ServerManager serverManager(8089);
    while (true) {
        serverManager.acceptConnection();
        std::thread serverThread([&]() {
            while (true) {
            if (!serverManager.start()) {
                break;
            }
            }
        });
        serverThread.detach();
        }
    return 0;
}
