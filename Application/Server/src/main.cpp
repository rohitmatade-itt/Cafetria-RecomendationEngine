#include <iostream>

#include "ServerSocket.h"
#include "DatabaseManager.h"

int main() {
    // ServerSocket server(8080);
    // server.acceptConnection();
    // std::cout << server.receiveMessage() << std::endl;

    DatabaseManager db;
    // db.executeQuery("SELECT * FROM User;");

    std::vector<std::vector<std::string>> data = db.fetchData("SELECT * FROM User;");
    for (auto row : data) {
        for (auto column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    return 0;
    
}
