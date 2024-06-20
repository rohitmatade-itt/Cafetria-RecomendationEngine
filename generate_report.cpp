#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <memory> // Include for std::unique_ptr
#include <mysql_driver.h> // Include MySQL C++ Connector headers
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

struct Feedback {
    int item_id;
    int taste_ratings;
    int quality_ratings;
    int overall_ratings;
    std::string date;
};

struct Vote {
    int item_id;
    std::string date;
    bool status;
};

struct MenuItem {
    int item_id;
    std::string item_name;
    double cost_price;
    double selling_price;
};

std::vector<Feedback> fetchFeedbackFromDB(const std::string& startDate, const std::string& endDate) {
    std::vector<Feedback> feedbacks;
    try {
        sql::Driver *driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "rohitmatade", "Code#ub$7"));
        con->setSchema("cafeteria");

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT item_id, taste_ratings, quality_ratings, overall_ratings, date FROM Feedback WHERE date BETWEEN ? AND ?"));
        pstmt->setString(1, startDate);
        pstmt->setString(2, endDate);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            Feedback feedback;
            feedback.item_id = res->getInt("item_id");
            feedback.taste_ratings = res->getInt("taste_ratings");
            feedback.quality_ratings = res->getInt("quality_ratings");
            feedback.overall_ratings = res->getInt("overall_ratings");
            feedback.date = res->getString("date");
            feedbacks.push_back(feedback);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }

    return feedbacks;
}

std::vector<Vote> fetchVotesFromDB(const std::string& startDate, const std::string& endDate) {
    std::vector<Vote> votes;
    try {
        sql::Driver *driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "rohitmatade", "Code#ub$7"));
        con->setSchema("cafeteria");

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT item_id, date, status FROM Vote WHERE date BETWEEN ? AND ?"));
        pstmt->setString(1, startDate);
        pstmt->setString(2, endDate);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            Vote vote;
            vote.item_id = res->getInt("item_id");
            vote.date = res->getString("date");
            vote.status = res->getBoolean("status");
            votes.push_back(vote);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }

    return votes;
}

std::vector<MenuItem> fetchMenuItemsFromDB() {
    std::vector<MenuItem> menuItems;
    try {
        sql::Driver *driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "rohitmatade", "Code#ub$7"));
        con->setSchema("cafeteria");

        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT item_id, item_name, cost_price, selling_price FROM Menu"));

        while (res->next()) {
            MenuItem menuItem;
            menuItem.item_id = res->getInt("item_id");
            menuItem.item_name = res->getString("item_name");
            menuItem.cost_price = res->getDouble("cost_price");
            menuItem.selling_price = res->getDouble("selling_price");
            menuItems.push_back(menuItem);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }

    return menuItems;
}

void generateReport(const std::vector<Feedback>& feedbacks, const std::vector<Vote>& votes, const std::vector<MenuItem>& menuItems) {
    std::unordered_map<int, std::vector<int>> tasteRatingsMap;
    std::unordered_map<int, std::vector<int>> qualityRatingsMap;
    std::unordered_map<int, std::vector<int>> overallRatingsMap;
    std::unordered_map<int, int> voteCountMap;

    for (const auto& feedback : feedbacks) {
        tasteRatingsMap[feedback.item_id].push_back(feedback.taste_ratings);
        qualityRatingsMap[feedback.item_id].push_back(feedback.quality_ratings);
        overallRatingsMap[feedback.item_id].push_back(feedback.overall_ratings);
    }

    for (const auto& vote : votes) {
        if (vote.status) {
            voteCountMap[vote.item_id]++;
        }
    }

    std::cout << "+----------------------+-------+---------------------+----------------------+----------------------+---------------+" << std::endl;
    std::cout << "| Item Name            | Votes | Avg. Taste Rating   | Avg. Quality Rating  | Avg. Overall Rating  | Total Profit  |" << std::endl;
    std::cout << "+----------------------+-------+---------------------+----------------------+----------------------+---------------+" << std::endl;

    for (const auto& menuItem : menuItems) {
        int item_id = menuItem.item_id;
        const std::string& item_name = menuItem.item_name;

        double avgTasteRating = tasteRatingsMap[item_id].empty() ? 0 : std::accumulate(tasteRatingsMap[item_id].begin(), tasteRatingsMap[item_id].end(), 0.0) / tasteRatingsMap[item_id].size();
        double avgQualityRating = qualityRatingsMap[item_id].empty() ? 0 : std::accumulate(qualityRatingsMap[item_id].begin(), qualityRatingsMap[item_id].end(), 0.0) / qualityRatingsMap[item_id].size();
        double avgOverallRating = overallRatingsMap[item_id].empty() ? 0 : std::accumulate(overallRatingsMap[item_id].begin(), overallRatingsMap[item_id].end(), 0.0) / overallRatingsMap[item_id].size();

        int votes = voteCountMap[item_id];
        double totalProfit = votes * (menuItem.selling_price - menuItem.cost_price);

        std::cout << "| " << std::left << std::setw(20) << item_name << " | " 
                  << std::setw(5) << votes << " | " 
                  << std::setw(19) << std::fixed << std::setprecision(2) << avgTasteRating << " | " 
                  << std::setw(20) << std::fixed << std::setprecision(2) << avgQualityRating << " | "
                  << std::setw(20) << std::fixed << std::setprecision(2) << avgOverallRating << " | "
                  << std::setw(13) << std::fixed << std::setprecision(2) << totalProfit << " |" << std::endl;
    }

    std::cout << "+----------------------+-------+---------------------+----------------------+----------------------+---------------+" << std::endl;
}

int main() {
    std::string startDate, endDate;
    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::cin >> startDate;
    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::cin >> endDate;

    std::vector<Feedback> feedbacks = fetchFeedbackFromDB(startDate, endDate);
    std::vector<Vote> votes = fetchVotesFromDB(startDate, endDate);
    std::vector<MenuItem> menuItems = fetchMenuItemsFromDB();

    generateReport(feedbacks, votes, menuItems);

    return 0;
}
