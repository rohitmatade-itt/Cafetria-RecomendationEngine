#ifndef FEEDBACK_DTO_H
#define FEEDBACK_DTO_H

#include <string>

class FeedbackDTO
{
public:
    int feedback_id;
    int item_id;
    std::string user_name;
    std::string date;
    int taste_rating;
    int quantity_rating;
    int overall_rating;
    std::string comment;

    std::string feedbackDTO_serialiser();
    void feedbackDTO_deserialiser(std::string);
};

#endif // FEEDBACK_DTO_H