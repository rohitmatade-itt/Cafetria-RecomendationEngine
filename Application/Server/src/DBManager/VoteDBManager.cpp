#include "VoteDBManager.h"

#include <sstream>

bool VoteDBManager::voteMenu(std::string message) {
    bool response;

    std::vector<std::string> elements;
    std::stringstream ss(message);
    std::string element;

    while (std::getline(ss, element, '\t')) {
        elements.push_back(element);
    }

    std::cout << "Item ID: " << elements[0] << std::endl;
    std::cout << "User Name: " << elements[1] << std::endl;

    std::string query = "INSERT INTO Vote (item_id, user_name, date) VALUES ('" + elements[0] + "', '" + elements[1] + "', DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY))";
    if(dbManager.executeUpdate(query)) {
        response = true;
    } else {
        response = false;
    }

    return response;
}

std::string VoteDBManager::getVotes(std::string message) {
    std::string query = "SELECT vm.item_id, m.item_name, rm.meal_type, COUNT(vm.item_id) "
                        "FROM Vote vm "
                        "JOIN Menu m ON vm.item_id = m.item_id "
                        "JOIN RolloutMenu rm ON m.item_id = rm.item_id "
                        "WHERE vm.date = DATE_ADD(CURRENT_DATE, INTERVAL 1 DAY) "
                        "GROUP BY vm.item_id, m.item_name, rm.meal_type";
    
    auto result = dbManager.fetchData(query);

    std::string tabSeparatedString;
    for (const auto& row : result) {
        for (const auto& field : row) {
            tabSeparatedString += field + "\t";
        }
        tabSeparatedString += "\n";
    }

    return tabSeparatedString;
}
