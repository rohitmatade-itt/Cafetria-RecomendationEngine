#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "User.h"
#include "MockClientSocket.h"
#include "RequestType.h"

class UserTest : public ::testing::Test {
protected:
    MockClientSocket mockClientSocket;
    User user;

    UserTest() : user(mockClientSocket) {}
    ~UserTest() override = default;
};

class TestableUser : public User {
public:
    using User::User;
    using User::getInput;
    using User::isValidDate;
    using User::displayMenuItems;
};

TEST_F(UserTest, GetInput) {
    TestableUser testableUser(mockClientSocket);
    std::istringstream input("TestInput");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(testableUser.getInput("Enter input: "), "TestInput");
}

TEST_F(UserTest, IsValidDate) {
    TestableUser testableUser(mockClientSocket);
    EXPECT_TRUE(testableUser.isValidDate("2024-07-07"));
    EXPECT_FALSE(testableUser.isValidDate("07-07-2024"));
}

TEST_F(UserTest, DisplayMenuItems) {
    TestableUser testableUser(mockClientSocket);
    std::vector<std::string> menuItems = {"Item1", "Item2", "Item3"};
    testing::internal::CaptureStdout();
    testableUser.displayMenuItems(menuItems, "2024-07-07");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Menu Items for 2024-07-07:"), std::string::npos);
    EXPECT_NE(output.find("1. Item1"), std::string::npos);
    EXPECT_NE(output.find("2. Item2"), std::string::npos);
    EXPECT_NE(output.find("3. Item3"), std::string::npos);
}

TEST_F(UserTest, UserLoginSuccess) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::LOGIN_REQUEST), ::testing::_)).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("Login successful"));
    EXPECT_EQ(user.userLogin(), "Login successful");
}

TEST_F(UserTest, GetFullName) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::GET_FULL_NAME), "username")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("John Doe"));
    EXPECT_EQ(user.getFullName("username"), "John Doe");
}

TEST_F(UserTest, DisplayMenu) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::DISPLAY_MENU_REQUEST), "")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("Item1\tItem2\tItem3"));
    testing::internal::CaptureStdout();
    user.displayMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Item1"), std::string::npos);
    EXPECT_NE(output.find("Item2"), std::string::npos);
    EXPECT_NE(output.find("Item3"), std::string::npos);
}

TEST_F(UserTest, ViewSpecificDateMenu) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::VIEW_SPECIFIC_DATE_MENU_REQUEST), "2024-07-07")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("Item1\tItem2\tItem3"));
    testing::internal::CaptureStdout();
    std::istringstream input("2024-07-07\n");
    std::cin.rdbuf(input.rdbuf());
    user.viewSpecificDateMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Item1"), std::string::npos);
    EXPECT_NE(output.find("Item2"), std::string::npos);
    EXPECT_NE(output.find("Item3"), std::string::npos);
}

TEST_F(UserTest, UpdateNotificationToAll) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::UPDATE_NOTIFICATION_ALL), "Notification")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("Notification sent"));
    testing::internal::CaptureStdout();
    user.updateNotificationToAll("Notification");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Notification sent"), std::string::npos);
}

TEST_F(UserTest, UpdateNotificationToEmployee) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::UPDATE_NOTIFICATION_EMPLOYEE), "Notification")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("Notification sent"));
    testing::internal::CaptureStdout();
    user.updateNotificationToEmployee("Notification");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Notification sent"), std::string::npos);
}

TEST_F(UserTest, GetNotificationIfAnyWithNotification) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::GET_NOTIFICATION), "username")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return("Notification"));
    testing::internal::CaptureStdout();
    user.getNotificationIfAny("username");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Notification"), std::string::npos);
}

TEST_F(UserTest, GetNotificationIfAnyWithoutNotification) {
    EXPECT_CALL(mockClientSocket, sendMessage(static_cast<int>(RequestType::GET_NOTIFICATION), "username")).Times(1);
    EXPECT_CALL(mockClientSocket, receiveMessage()).WillOnce(::testing::Return(""));
    testing::internal::CaptureStdout();
    user.getNotificationIfAny("username");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No new notifications"), std::string::npos);
}
