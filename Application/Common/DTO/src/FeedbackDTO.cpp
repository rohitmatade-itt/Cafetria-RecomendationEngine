#include <iostream>
#include "FeedbackDTO.h"

enum class FeedbackDTOField {
    FeedbackID,
    ItemID,
    UserName,
    Date,
    TasteRating,
    QuantityRating,
    OverallRating,
    Comment
};

std::string FeedbackDTO::feedbackDTO_serialiser()
{
    std::string serialised_feedback;
    serialised_feedback = std::to_string(feedback_id) + "\t" + std::to_string(item_id) + "\t" + user_name + "\t" + date + "\t" + std::to_string(taste_rating) + "\t" + std::to_string(quantity_rating) + "\t" + std::to_string(overall_rating) + "\t" + comment;
    return serialised_feedback;
}

void FeedbackDTO::feedbackDTO_deserialiser(std::string serialised_feedback)
{
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int fieldIndex = 0;
    while ((pos = serialised_feedback.find(delimiter)) != std::string::npos)
    {
        token = serialised_feedback.substr(0, pos);
        switch (static_cast<FeedbackDTOField>(fieldIndex))
        {
        case FeedbackDTOField::FeedbackID:
            feedback_id = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case FeedbackDTOField::ItemID:
            item_id = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case FeedbackDTOField::UserName:
            user_name = !token.empty() ? token : "";
            break;
        case FeedbackDTOField::Date:
            date = !token.empty() ? token : "";
            break;
        case FeedbackDTOField::TasteRating:
            taste_rating = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case FeedbackDTOField::QuantityRating:
            quantity_rating = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case FeedbackDTOField::OverallRating:
            overall_rating = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case FeedbackDTOField::Comment:
            comment = !token.empty() ? token : "";
            break;
        default:
            break;
        }
        serialised_feedback.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}