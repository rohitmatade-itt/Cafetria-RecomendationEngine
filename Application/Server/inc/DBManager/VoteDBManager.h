#ifndef VOTE_DBMANAGER_H
#define VOTE_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class VoteDBManager {
public:
    VoteDBManager(sql::Connection* dbConnection);
    ~VoteDBManager();

    bool addVote(int itemId, const std::string& userName, const std::string& date, int status);
    bool updateVote(int voteId, int itemId, const std::string& userName, const std::string& date, int status);
    bool deleteVote(int voteId);
    std::vector<std::vector<std::string>> getAllVotes();
    std::vector<std::string> getVoteById(int voteId);

private:
    sql::Connection* connection;

    bool executeQuery(const std::string& query);
};

#endif // VOTE_DBMANAGER_H
