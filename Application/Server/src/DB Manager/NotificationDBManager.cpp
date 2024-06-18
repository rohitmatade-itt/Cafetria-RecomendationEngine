#include "NotificationDBManager.h"

NotificationDBManager::NotificationDBManager(sql::Connection* dbConnection) : connection(dbConnection) {}

NotificationDBManager::~NotificationDBManager() {
    // Destructor: No need for explicit cleanup of the `connection` object since it's managed externally.
}

bool NotificationDBManager::addNotification(const std::string& userName, const std::string& message) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("INSERT INTO Notification (user_name, message, read_receipt) VALUES (?, ?, 0)");
        stmt->setString(1, userName);
        stmt->setString(2, message);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error adding notification: " << e.what() << std::endl;
        return false;
    }
}

bool NotificationDBManager::updateNotification(int notificationId, const std::string& userName, const std::string& message, bool readReceipt) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("UPDATE Notification SET user_name=?, message=?, read_receipt=? WHERE notification_id=?");
        stmt->setString(1, userName);
        stmt->setString(2, message);
        stmt->setBoolean(3, readReceipt);
        stmt->setInt(4, notificationId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error updating notification: " << e.what() << std::endl;
        return false;
    }
}

bool NotificationDBManager::deleteNotification(int notificationId) {
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("DELETE FROM Notification WHERE notification_id=?");
        stmt->setInt(1, notificationId);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error deleting notification: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::vector<std::string>> NotificationDBManager::getAllNotifications() {
    std::vector<std::vector<std::string>> notifications;
    try {
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Notification");

        while (res->next()) {
            std::vector<std::string> notification;
            notification.push_back(std::to_string(res->getInt("notification_id")));
            notification.push_back(res->getString("user_name"));
            notification.push_back(res->getString("created_time"));
            notification.push_back(res->getString("message"));
            notification.push_back(std::to_string(res->getBoolean("read_receipt")));
            notifications.push_back(notification);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching notifications: " << e.what() << std::endl;
    }

    return notifications;
}

std::vector<std::string> NotificationDBManager::getNotificationById(int notificationId) {
    std::vector<std::string> notification;
    try {
        sql::PreparedStatement *stmt = connection->prepareStatement("SELECT * FROM Notification WHERE notification_id=?");
        stmt->setInt(1, notificationId);
        sql::ResultSet *res = stmt->executeQuery();

        if (res->next()) {
            notification.push_back(std::to_string(res->getInt("notification_id")));
            notification.push_back(res->getString("user_name"));
            notification.push_back(res->getString("created_time"));
            notification.push_back(res->getString("message"));
            notification.push_back(std::to_string(res->getBoolean("read_receipt")));
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error fetching notification: " << e.what() << std::endl;
    }

    return notification;
}

bool NotificationDBManager::executeQuery(const std::string& query) {
    try {
        sql::Statement *stmt = connection->createStatement();
        stmt->execute(query);
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        return false;
    }
}
