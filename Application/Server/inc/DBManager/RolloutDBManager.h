#ifndef ROLLOUT_DBMANAGER_H
#define ROLLOUT_DBMANAGER_H

#include <iostream>
#include <vector>
#include <string>

#include "DatabaseManager.h"

class RollOutDBManager {
public:
    std::vector<std::string> getRollOutByDate(std::string date);
private:
    DatabaseManager dbManager;
};

#endif // ROLLOUT_DBMANAGER_H
