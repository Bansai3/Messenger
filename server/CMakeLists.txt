cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(Boost_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.83.0/include)
set(Boost_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.83.0/lib)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(server
  main.cpp
  Session.h
  Session.cpp
  FailHandler.h
  FailHandler.cpp
  Listener.h
  Listener.cpp

  UsersStorage.h
  User.h
  User.cpp
  UsersStorage.cpp
  UserConstants.h

  Namespaces.h

  PortConnectionState.h

  UsersGroup.h
  UsersGroup.cpp
  Message.h
  Message.cpp
  PersonalCorrespondence.h
  PersonalCorrespondence.cpp


)
target_link_libraries(server Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
