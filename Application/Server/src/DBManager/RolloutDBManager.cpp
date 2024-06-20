#include "RollOutDBManager.h"

std::vector<std::string> RollOutDBManager::getRollOutByDate(std::string date)
{
    std::vector<std::string> menu_list;
    std::string query = "SELECT item_name FROM Menu WHERE item_id IN (SELECT item_id FROM RolloutMenu WHERE rollout_date = '" + date + "')";
    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        menu_list.push_back(row[0]);
    }
    return menu_list;
}

std::string RollOutDBManager::rolloutMenu(std::string item_id)
{
    std::string query = "INSERT INTO RolloutMenu (item_id, rollout_date) VALUES ('" + item_id + "', DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY))";
    dbManager.executeUpdate(query);
    return "Menu rolled out successfully";
}

std::string RollOutDBManager::getRolloutMenu(std::string message)
{
    std::string query = "SELECT * FROM RolloutMenu WHERE rollout_date = DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY)";
    auto result = dbManager.fetchData(query);
    std::string tabSeparatedString;
    for (auto row : result) {
        for (auto column : row) {
            tabSeparatedString += column + "\t";
        }
        tabSeparatedString += "\n";
    }
    return tabSeparatedString;
}

// std::string RollOutDBManager::generateReport(std::string start_date, std::string end_date)
// {
//     std::vector<std::string> report;

//     std::string query = "";
//     auto result = dbManager.fetchData(query);
//     for (auto row : result) {
//         std::string report_item;
//         for (auto column : row) {
//             report_item += column + "\t";
//         }
//         report.push_back(report_item);
//         printf("%s\n", report_item.c_str());
//     }
//     return "Hi";
// }
