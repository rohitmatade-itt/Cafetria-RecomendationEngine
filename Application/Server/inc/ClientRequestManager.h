#ifndef CLIENTREQUESTMANAGER_H
#define CLIENTREQUESTMANAGER_H

#include <string>

class ClientRequestManager {
public:
    std::string loginRequest(std::string message);
    std::string displayMenuRequest(std::string message);
    std::string viewSpecificDateMenuRequest(std::string message);
    bool addEmployeeRequest(std::string message);
    bool removeEmployeeRequest(std::string message);
    bool addMenuItemRequest(std::string message);
    bool removeMenuItemRequest(std::string message);
    // std::string generateReportRequest(std::string message);
    std::string getRecommendedListRequest(std::string message);
    std::string rolloutNextDayMenuRequest(std::string message);
    std::string getNextDayMenuRequest(std::string message);
};

#endif // CLIENTREQUESTMANAGER_H