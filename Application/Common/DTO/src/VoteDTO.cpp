#include "VoteDTO.h"

enum class VoteDTOField {
    VoteID,
    ItemID,
    UserName,
    Date,
    Status
};

std::string VoteDTO::voteDTO_serialiser()
{
    std::string serialised_vote;
    serialised_vote = std::to_string(vote_id) + "\t" + std::to_string(item_id) + "\t" + user_name + "\t" + date + "\t" + std::to_string(status);
    return serialised_vote;
}

void VoteDTO::voteDTO_deserialiser(std::string serialised_vote)
{
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int fieldIndex = 0;
    while ((pos = serialised_vote.find(delimiter)) != std::string::npos)
    {
        token = serialised_vote.substr(0, pos);
        switch (static_cast<VoteDTOField>(fieldIndex))
        {
        case VoteDTOField::VoteID:
            vote_id = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case VoteDTOField::ItemID:
            item_id = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        case VoteDTOField::UserName:
            user_name = !token.empty() ? token : "";
            break;
        case VoteDTOField::Date:
            date = !token.empty() ? token : "";
            break;
        case VoteDTOField::Status:
            status = !token.empty() ? static_cast<int>(token[0]) : 0;
            break;
        default:
            break;
        }
        serialised_vote.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}