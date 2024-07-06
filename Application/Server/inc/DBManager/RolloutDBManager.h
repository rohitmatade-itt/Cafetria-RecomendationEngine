#ifndef ROLLOUT_DBMANAGER_H
#define ROLLOUT_DBMANAGER_H

#include "DatabaseManager.h"
#include "RecommendationDTO.h"

class RollOutDBManager {
public:
    std::vector<std::string> getRollOutByDate(std::string date);
    bool rolloutMenu(std::string item_id);
    std::string getRolloutMenu(std::string message);
    std::vector<Rollout> fetchRollouts();
    // std::string generateReport(std::string start_date, std::string end_date);
private:
    DatabaseManager dbManager;
};

#endif // ROLLOUT_DBMANAGER_H
