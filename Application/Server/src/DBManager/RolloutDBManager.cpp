#include <sstream>

#include "RollOutDBManager.h"
#include "RecommendationDTO.h"

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

bool RollOutDBManager::rolloutMenu(std::string message)
{
    std::vector<std::string> elements;
    std::stringstream ss(message);
    std::string element;
    bool response;

    while (std::getline(ss, element, '\t')) {
        elements.push_back(element);
    }
    std::string query = "INSERT INTO RolloutMenu (item_id, meal_type, rollout_date) VALUES ('" + elements[0] + "','" + elements[1] + "', DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY))";

    if(dbManager.executeUpdate(query)) {
        response = true;
    } else {
        response = false;
    }
    return response;
}

std::string RollOutDBManager::getRolloutMenu(std::string message)
{
    std::string tabSeparatedString;

    try {
        std::string query = "SELECT rm.item_id, m.item_name, rm.meal_type "
                            "FROM RolloutMenu rm "
                            "JOIN Menu m ON rm.item_id = m.item_id "
                            "WHERE rm.rollout_date = DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY)";
        
        auto result = dbManager.fetchData(query);
        
        for (auto& row : result) {
            if (row.size() >= 3) {
                tabSeparatedString += row[0] + "\t" + row[1] + "\t" + row[2] + "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error fetching data: " << e.what() << std::endl;
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

std::vector<Rollout> RollOutDBManager::fetchRollouts()
{
    std::vector<Rollout> rollouts;
    std::string query = "SELECT rm.item_id, rm.meal_type, m.diet_type, m.spice_level, m.cuisine_type, m.sweet_type "
                        "FROM RolloutMenu rm "
                        "JOIN Menu m ON rm.item_id = m.item_id "
                        "WHERE rm.rollout_date = DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY)";

    auto result = dbManager.fetchData(query);
    for (auto row : result) {
        Rollout rollout;

        rollout.item_id = row[0];
        rollout.meal_type = row[1];
        rollout.diet_type = row[2];
        rollout.spice_level = row[3];
        rollout.cuisine_type = row[4];
        rollout.sweet_type = row[5];
        
        rollouts.push_back(rollout);
    }
    return rollouts; 
}