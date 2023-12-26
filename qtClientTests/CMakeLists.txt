cmake_minimum_required(VERSION 3.5)

project(clientQtTests LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Test Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets Network WebSockets)

set(Boost_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.83.0/include)
set(Boost_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.83.0/lib)

find_package(Boost REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clientQtTests tst_clientqttests.cpp
    ../client/authentication.cpp ../client/authentication.h ../client/authentication.ui ../client/chat.cpp ../client/chat.h ../client/chat.ui
    ../client/DeviceController.cpp ../client/DeviceController.h ../client/mainwindow.cpp ../client/mainwindow.h ../client/mainwindow.ui ../client/sign_in.cpp ../client/sign_in.h ../client/sign_in.ui ../client/sign_up.cpp ../client/sign_up.h ../client/sign_up.ui
    ../server/FailHandler.cpp ../server/FailHandler.h ../server/Listener.cpp ../server/Listener.h ../server/Session.cpp ../server/Session.h ../server/SessionsHandler.h ../server/User.cpp ../server/User.h ../server/UserConstants.h ../server/UsersStorage.cpp ../server/UsersStorage.h

)
add_test(NAME clientQtTests COMMAND clientQtTests)

target_link_libraries(clientQtTests PRIVATE Qt6::Network Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test Qt6::WebSockets)
target_link_libraries(clientQtTests PUBLIC Qt6::Core Qt6::WebSockets)

include_directories(/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/course_project_2/client)
include_directories(/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/course_project_2/server)
