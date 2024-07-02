#include <iostream>
#include "ServerManager.h"

int main() {
    ServerManager serverManager(8089);
    while (true) {
        std::cout << "req started" << std::endl;
        serverManager.start();
        std::cout << "req ended" << std::endl;
    }
    return 0;
}
