#include "NotificationDTO.h"

enum class NotificationDTOField {
    NotificationID,
    UserName,
    CreatedTime,
    Message,
    ReadReceipt
};

std::string NotificationDTO::notificationDTO_serialiser()
{
    std::string serialised_notification;
    serialised_notification = std::to_string(notification_id) + "\t" + user_name + "\t" + created_time + "\t" + message + "\t" + std::to_string(read_receipt);
    return serialised_notification;
}

void NotificationDTO::notificationDTO_deserialiser(std::string serialised_notification)
{
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int fieldIndex = 0;
    while ((pos = serialised_notification.find(delimiter)) != std::string::npos)
    {
        token = serialised_notification.substr(0, pos);
        switch (static_cast<NotificationDTOField>(fieldIndex))
        {
        case NotificationDTOField::NotificationID:
            notification_id = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case NotificationDTOField::UserName:
            user_name = !token.empty() ? token : "";
            break;
        case NotificationDTOField::CreatedTime:
            created_time = !token.empty() ? token : "";
            break;
        case NotificationDTOField::Message:
            message = !token.empty() ? token : "";
            break;
        case NotificationDTOField::ReadReceipt:
            read_receipt = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        default:
            break;
        }
        serialised_notification.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}