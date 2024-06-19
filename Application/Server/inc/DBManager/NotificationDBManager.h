#ifndef NOTIFICATION_DBMANAGER_H
#define NOTIFICATION_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class NotificationDBManager {
public:
    NotificationDBManager(sql::Connection* dbConnection);
    ~NotificationDBManager();

    bool addNotification(const std::string& userName, const std::string& message);
    bool updateNotification(int notificationId, const std::string& userName, const std::string& message, bool readReceipt);
    bool deleteNotification(int notificationId);
    std::vector<std::vector<std::string>> getAllNotifications();
    std::vector<std::string> getNotificationById(int notificationId);

private:
    sql::Connection* connection;

    bool executeQuery(const std::string& query);
};

#endif // NOTIFICATION_DBMANAGER_H
