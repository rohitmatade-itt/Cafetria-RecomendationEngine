#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string user_name;
    std::string first_name;
    std::string last_name;
    std::string employee_id;
public:
    User();
    User(const std::string& user_name, const std::string& first_name, const std::string& last_name, const std::string& employee_id);

    bool userLogin();

    std::string getUserName() const;
    void setUserName(const std::string& user_name);

    std::string getFirstName() const;
    void setFirstName(const std::string& first_name);

    std::string getLastName() const;
    void setLastName(const std::string& last_name);

    std::string getEmployeeId() const;
    void setEmployeeId(const std::string& employee_id);

    void displayUserInfo() const;
    void userWelcome() const;
    void displayMenu() const;
};

#endif // USER_H
