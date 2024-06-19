#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>

namespace Utils {
    void displayOptions(const std::vector<std::string>& menuOptions, int selectedOption);
    int selectOption(const std::vector<std::string>& menuOptions);
    std::vector<std::string> splitStringbyTab(std::string str);

}

#endif // UTILS_H
