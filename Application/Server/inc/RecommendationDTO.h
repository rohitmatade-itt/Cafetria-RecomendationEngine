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

struct Rollout {
    std::string item_id;
    std::string meal_type;
    std::string diet_type;
    std::string spice_level;
    std::string cuisine_type;
    std::string sweet_type;
};

struct UserPreference {
    std::string diet_preference;
    std::string spice_level;
    std::string prefered_cuisine;
    std::string sweet_preference;
};

#endif // RECOMMENDATION_DTO_H