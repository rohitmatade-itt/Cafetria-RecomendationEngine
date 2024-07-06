#ifndef CLIENTREQUESTMANAGER_H
#define CLIENTREQUESTMANAGER_H

#include <string>
#include <vector>

#include "RecommendationDTO.h"

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
    bool rolloutNextDayMenuRequest(std::string message);
    std::string getNextDayMenuRequest(std::string message);
    bool voteNextDayMenuRequest(std::string message);
    bool giveFeedbackRequest(std::string message);
    std::string viewNextDayVotesRequest(std::string message);
    std::string getUserVoteListRequest(std::string message);
    std::string getUserProfileRequest(std::string message);
    bool updateUserProfileRequest(std::string message);
    std::string getUserRecommendedListRequest(std::string message);
};

#endif // CLIENTREQUESTMANAGER_H