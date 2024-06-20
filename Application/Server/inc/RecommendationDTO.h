#ifndef RECOMMENDATION_DTO_H
#define RECOMMENDATION_DTO_H

#include <string>

struct Feedback {
    int item_id;
    int taste_ratings;
    int quality_ratings;
    int overall_ratings;
    std::string comment;
};

struct MenuItem {
    int item_id;
    std::string item_name;
    double cost_price;
    double selling_price;
};

#endif // RECOMMENDATION_DTO_H