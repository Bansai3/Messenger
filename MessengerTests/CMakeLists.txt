cmake_minimum_required(VERSION 3.5)

project(ClientTest LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Test Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets Network WebSockets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ClientTest tst_clienttest.cpp     ../client/chat.cpp ../client/chat.h ../client/chat.ui
    ../client/DeviceController.cpp ../client/DeviceController.h ../client/mainwindow.cpp
    ../client/mainwindow.h ../client/mainwindow.ui ../client/sign_in.cpp ../client/sign_in.h
    ../client/sign_in.ui ../client/sign_up.cpp ../client/sign_up.h ../client/sign_up.ui)
add_test(NAME ClientTest COMMAND ClientTest)


target_link_libraries(ClientTest PRIVATE Qt6::Network Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test Qt6::WebSockets)
target_link_libraries(ClientTest PUBLIC Qt6::Core Qt6::WebSockets)


include_directories(/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/course_project/client)
