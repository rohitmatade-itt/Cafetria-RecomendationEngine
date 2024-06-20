#include <iostream>
#include <ncurses.h>

#include "Utils.h"

namespace Utils {

    void displayOptions(const std::vector<std::string>& menuOptions, int selectedOption) {
        clear();

        for (int index = 0; index < menuOptions.size(); ++index) {
            if (index == selectedOption) {
                attron(A_REVERSE);
                printw("-> %s\n", menuOptions[index].c_str());
                attroff(A_REVERSE);
            } else {
                printw("   %s\n", menuOptions[index].c_str());
            }
        }
    }

    int selectOption(const std::vector<std::string>& menuOptions) {
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);

        int selectedOption = 0;
        displayOptions(menuOptions, selectedOption);

        while (true) {
            int userInput = getch();

            switch (userInput) {
                case KEY_UP:
                    selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
                    displayOptions(menuOptions, selectedOption);
                    break;
                case KEY_DOWN:
                    selectedOption = (selectedOption + 1) % menuOptions.size();
                    displayOptions(menuOptions, selectedOption);
                    break;
                case '\n':
                    endwin();
                    return selectedOption;
                default:
                    break;
            }
        }

        return -1;
    }

    std::vector<std::string> splitStringbyTab(std::string str) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, '\t')) {
            result.push_back(token);
        }
        
        return result;
    }

    std::string removeResponseType(std::string response) {
        return response.substr(response.find('\t') + 1);
    }
}
