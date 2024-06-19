#ifndef VOTE_DTO_H
#define VOTE_DTO_H

#include <string>

class VoteDTO
{
public:
    int vote_id;
    int item_id;
    std::string user_name;
    std::string date;
    bool status;

    std::string voteDTO_serialiser();
    void voteDTO_deserialiser(std::string);
};

#endif // VOTE_DTO_H