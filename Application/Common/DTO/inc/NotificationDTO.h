#ifndef NOTIFICATION_DTO_H
#define NOTIFICATION_DTO_H

#include <string>

class NotificationDTO
{
public:
    int notification_id;
    std::string user_name;
    std::string created_time;
    std::string message;
    bool read_receipt;

    std::string notificationDTO_serialiser();
    void notificationDTO_deserialiser(std::string);
};

#endif // NOTIFICATION_DTO_H