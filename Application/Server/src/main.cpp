#include "ServerManager.h"

int main() {
    ServerManager serverManager(8089);
    while (true) {
        serverManager.start();
    }
    return 0;
}
