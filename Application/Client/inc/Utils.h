#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {
    void displayOptions(const std::vector<std::string>& menuOptions, int selectedOption);
    int selectOption(const std::vector<std::string>& menuOptions);
}

#endif // UTILS_H
