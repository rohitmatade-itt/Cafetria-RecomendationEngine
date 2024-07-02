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
        refresh();
    }

    int selectOption(const std::vector<std::string>& menuOptions) {
        initscr(); // Initializes ncurses
        keypad(stdscr, TRUE); // Enables reading special keys

        int selectedOption = 0;
        displayOptions(menuOptions, selectedOption);

        int userInput;
        while (true) {
            userInput = getch();

            if (userInput == KEY_UP) {
                selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
            } else if (userInput == KEY_DOWN) {
                selectedOption = (selectedOption + 1) % menuOptions.size();
            } else if (userInput == '\n') {
                break;
            }

            displayOptions(menuOptions, selectedOption);
        }

        endwin();
        return selectedOption;
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
