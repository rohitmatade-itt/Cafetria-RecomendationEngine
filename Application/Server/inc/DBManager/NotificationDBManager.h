#ifndef NOTIFICATION_DBMANAGER_H
#define NOTIFICATION_DBMANAGER_H

#include "DatabaseManager.h"
#include "UserDBManager.h"

class NotificationDBManager {
public:
    std::string fetchNotification(std::string username);
    bool addNotificationToAll(std::string message);
    bool addNotificationToEmployees(std::string message);
private:
    DatabaseManager dbManager;
    UserDBManager userDBManager;
};

#endif // NOTIFICATION_DBMANAGER_H