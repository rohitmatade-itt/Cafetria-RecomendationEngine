cmake_minimum_required(VERSION 3.10)
project(ClientTests)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Define source files for the main application
set(SOURCE_FILES
    Client/src/Admin.cpp
    Client/src/Chef.cpp
    Client/src/ClientSocket.cpp
    Client/src/Employee.cpp
    Client/src/User.cpp
    Client/src/Utils.cpp
    Common/DTO/src/UserDTO.cpp
    Server/src/ClientRequestManager.cpp
    Server/src/DBManager/DatabaseManager.cpp
    Server/src/DBManager/FeedbackDBManager.cpp
    Server/src/DBManager/MenuDBManager.cpp
    Server/src/DBManager/NotificationDBManager.cpp
    Server/src/DBManager/RolloutDBManager.cpp
    Server/src/DBManager/UserDBManager.cpp
    Server/src/DBManager/VoteDBManager.cpp
    Server/src/RecommendationEngine.cpp
    Server/src/SentimentAnalyzer.cpp
    Server/src/ServerManager.cpp
    Server/src/ServerSocket.cpp
)

# Define header files
set(HEADER_FILES
    Client/inc/Admin.h
    Client/inc/Chef.h
    Client/inc/ClientSocket.h
    Client/inc/Employee.h
    Client/inc/User.h
    Client/inc/Utils.h
    Common/DTO/inc/UserDTO.h
    Common/RequestType.h
    Common/ResponseType.h
    Common/SocketProtocol.h
    Server/inc/ClientRequestManager.h
    Server/inc/DBManager/DatabaseManager.h
    Server/inc/DBManager/FeedbackDBManager.h
    Server/inc/DBManager/MenuDBManager.h
    Server/inc/DBManager/NotificationDBManager.h
    Server/inc/DBManager/RolloutDBManager.h
    Server/inc/DBManager/UserDBManager.h
    Server/inc/DBManager/VoteDBManager.h
    Server/inc/RecommendationDTO.h
    Server/inc/RecommendationEngine.h
    Server/inc/SentimentAnalyzer.h
    Server/inc/ServerManager.h
    Server/inc/ServerSocket.h
)

# Add the main application executable
add_executable(main_app
    ${SOURCE_FILES}
    Client/src/main.cpp
)

# Add Google Test and Google Mock as external projects
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.10.0.zip
)
FetchContent_MakeAvailable(googletest)

# Include Google Test and Google Mock directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# Include directories for project headers
include_directories(Client/inc)
include_directories(Common/DTO/inc)
include_directories(Server/inc)
include_directories(Server/inc/DBManager)
include_directories(Common)  # Ensuring Common directory is included

# Find ncurses and MySQL connector libraries
find_package(Curses REQUIRED)
find_library(MYSQLCPP_CONN NAMES mysqlcppconn)

# Disable warnings as errors for GoogleTest
set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gmock PROPERTIES COMPILE_FLAGS "-w")

# Define test files
set(TEST_FILES
    Client/gtest/main.cpp
    Client/gtest/gtest_User.cpp
    Client/gtest/MockClientSocket.h
)

# Add test executable
add_executable(runClientTests
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${TEST_FILES}
)

# Link the main application with ncurses and MySQL connector libraries
target_link_libraries(main_app ${CURSES_LIBRARIES} ${MYSQLCPP_CONN})

# Link the test executable with Google Test, Google Mock, ncurses, and MySQL connector libraries
target_link_libraries(runClientTests gtest gmock pthread ${CURSES_LIBRARIES} ${MYSQLCPP_CONN})
