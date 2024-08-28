#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "ServerSocket.h"
#include "ClientRequestManager.h"

class ServerManager {
public:
    ServerManager(int port);
    ~ServerManager();

    bool start();
    void acceptConnection();

private:
    SocketRequest parseSocketRequest(std::string input);
    std::string handleClientRequest(std::string message);

    std::string loginRequest(std::string message);
    std::string getFullNameRequest(std::string message);
    std::string displayMenuRequest(std::string message);
    std::string viewSpecificDateMenuRequest(std::string message);
    std::string addEmployeeRequest(std::string message);
    std::string removeEmployeeRequest(std::string message);
    std::string addMenuItemRequest(std::string message);
    std::string removeMenuItemRequest(std::string message);
    std::string getRecommendationRequest(std::string message);
    std::string getUserRecommendedListRequest(std::string message);
    std::string rolloutNextDayMenuRequest(std::string message);
    std::string getNextDayMenuRequest(std::string message);
    std::string voteNextDayMenuRequest(std::string message);
    std::string giveFeedbackRequest(std::string message);
    std::string viewNextDayVotesRequest(std::string message);
    std::string getUserVoteListRequest(std::string message);
    std::string getUserProfileRequest(std::string message);
    std::string updateUserProfileRequest(std::string message);
    std::string updateNotificationRequest(std::string message);
    std::string updateNotificationEmployeesRequest(std::string message);
    std::string getNotificationRequest(std::string message);
    std::string getDiscardedMenuItemsRequest();
    std::string viewFeedbackRequest(std::string message);

    int port;
    ServerSocket* serverSocket;
    ClientRequestManager clientRequestManager;
};

#endif // SERVERMANAGER_H
