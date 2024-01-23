cmake_minimum_required(VERSION 3.5)

project(ServerTest LANGUAGES CXX)

enable_testing()


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

set(Boost_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.83.0/include)
set(Boost_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.83.0/lib)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network WebSockets Core)


if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/GoogleTestFramework/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/GoogleTestFramework/googletest")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

add_executable(ServerTest main.cpp tst_servertest.cpp
               ${GTestFiles}
               ../server/FailHandler.cpp ../server/FailHandler.h ../server/Listener.cpp
               ../server/Listener.h ../server/Message.cpp ../server/Message.h
               ../server/Namespaces.h ../server/PersonalCorrespondence.cpp ../server/PersonalCorrespondence.h
               ../server/PortConnectionState.h ../server/Session.cpp ../server/Session.h ../server/User.cpp ../server/User.h
               ../server/UserConstants.h ../server/UsersGroup.cpp ../server/UsersGroup.h ../server/UsersStorage.cpp ../server/UsersStorage.h)
add_test(NAME ServerTest COMMAND ServerTest)
target_link_libraries(ServerTest PRIVATE Threads::Threads Qt${QT_VERSION_MAJOR}::Core)

include_directories(/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/course_project/server)

