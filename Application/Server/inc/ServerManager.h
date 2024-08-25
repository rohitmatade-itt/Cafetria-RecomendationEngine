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
    ClientRequestManager clientRequestManager;
    SocketRequest parseSocketRequest(std::string input);
    std::string handleClientRequest(std::string message);

    std::string handleLoginRequest(std::string message);
    std::string handleGetFullNameRequest(std::string message);
    std::string handleDisplayMenuRequest(std::string message);
    std::string handleViewSpecificDateMenuRequest(std::string message);
    std::string handleAddEmployeeRequest(std::string message);
    std::string handleRemoveEmployeeRequest(std::string message);
    std::string handleAddMenuItemRequest(std::string message);
    std::string handleRemoveMenuItemRequest(std::string message);
    std::string handleGetRecommendationRequest(std::string message);
    std::string handleRolloutNextDayMenuRequest(std::string message);
    std::string handleGetNextDayMenuRequest(std::string message);
    std::string handleVoteNextDayMenuRequest(std::string message);
    std::string handleGiveFeedbackRequest(std::string message);
    std::string handleViewNextDayVotesRequest(std::string message);
    std::string handleGetUserVoteListRequest(std::string message);
    std::string handleGetUserProfileRequest(std::string message);
    std::string handleUpdateUserProfileRequest(std::string message);
    std::string handleUpdateNotificationRequest(std::string message);
    std::string handleUpdateNotificationEmployeesRequest(std::string message);
    std::string handleGetNotificationRequest(std::string message);
    std::string handleGetDiscardedMenuItemsRequest();
    std::string handleViewFeedbackRequest(std::string message);

    int port;
    ServerSocket* serverSocket;
};

#endif // SERVERMANAGER_H
