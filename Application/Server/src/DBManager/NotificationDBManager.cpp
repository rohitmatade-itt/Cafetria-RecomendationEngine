#include "NotificationDBManager.h"

std::string NotificationDBManager::fetchNotification(std::string username) {
    std::string notifications;
    std::string query = "SELECT message "
                    "FROM Notification "
                    "WHERE user_name = '" + username + "' "
                    "AND read_receipt = 0 "
                    "AND created_time >= NOW() - INTERVAL 2 DAY";

    auto result = dbManager.fetchData(query);

    std::cout << "Query: " << query << std::endl;

    for (auto row : result) {
        notifications += row[0] + "\n";
        std::cout << "row[0]: " << row[0] << "\n";
    }

    query = "UPDATE Notification "
            "SET read_receipt = 1 "
            "WHERE user_name = '" + username + "' "
            "AND read_receipt = 0 "
            "AND created_time >= NOW() - INTERVAL 2 DAY";

    dbManager.executeUpdate(query);

    return notifications;
}

bool NotificationDBManager::addNotificationToAll(std::string message) {
    std::vector<std::string> users = userDBManager.fetchAllEmployeeAndChef();
    for (std::string user : users) {
        std::string query = "INSERT INTO Notification (user_name, message) VALUES ('" + user + "', '" + message + "')";
        dbManager.executeUpdate(query);
    }
    return true;
}

bool NotificationDBManager::addNotificationToEmployees(std::string message) {
    std::vector<std::string> employees = userDBManager.fetchAllEmployees();
    for (std::string employee : employees) {
        std::string query = "INSERT INTO Notification (user_name, message) VALUES ('" + employee + "', '" + message + "')";
        dbManager.executeUpdate(query);
    }
    return true;
}