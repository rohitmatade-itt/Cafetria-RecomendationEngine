#ifndef CLIENTREQUESTMANAGER_H
#define CLIENTREQUESTMANAGER_H

#include <string>

class ClientRequestManager {
public:
    std::string loginRequest(std::string message);
    std::string displayMenuRequest(std::string message);
    std::string viewSpecificDateMenuRequest(std::string message);
};

#endif // CLIENTREQUESTMANAGER_H