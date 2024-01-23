#ifndef USERSGROUP_H
#define USERSGROUP_H

#include "User.h"
#include <map>
#include "Message.h"
#include <sstream>
#include <qDebug>
using namespace serverMessage;

class UsersGroup
{
private:
    std::string name_;
    User* admin_;
    std::unordered_map<std::string, User*> users_;
    std::vector<Message> messages_;

public:
    UsersGroup(std::string& name);

public:
    User* getUser(std::string& login);

    std::string& getName();

    void addUser(User* user);

    void removeUser(std::string& login);

    Message addMessage(std::string& message, User* user);

    bool containsUser(User* user);

    const std::vector<Message>& getMessages();

    std::string getAllMessages();

    void deleteMessage(std::string& messageToDelete);

    bool containsUser(std::string& userLogin);

    std::vector<std::string> getUsers();
};

#endif // USERSGROUP_H
