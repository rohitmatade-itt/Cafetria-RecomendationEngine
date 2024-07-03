#ifndef VOTE_DBMANAGER_H
#define VOTE_DBMANAGER_H

#include "DatabaseManager.h"

class VoteDBManager {
public:
    bool voteMenu(std::string message);
    std::string getVotes(std::string message);
private:
    DatabaseManager dbManager;
};

#endif // VOTE_DBMANAGER_H