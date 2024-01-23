#ifndef USERSSTORAGE_H
#define USERSSTORAGE_H

#include<map>
#include "User.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "UserConstants.h"
#include <QCoreApplication>

class UsersStorage
{
public:

    boost::property_tree::ptree addUser(User user);

    boost::property_tree::ptree getUser(std::string login, std::string password);

    User* getUser(std::string& login);

    std::vector<std::string> getUsers();

private:
    std::map<std::string, User> users_;

    bool checkUserParameters(User* user);

    bool checkLogin(std::string login);

    bool checkPassword(std::string password);

    bool checkName(std::string name);

    bool checkSurname(std::string surname);

    bool checkAlphaAndDigitString(std::string str);

    bool checkAlphaString(std::string str);
};

#endif // USERSSTORAGE_H
