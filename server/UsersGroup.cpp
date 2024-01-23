#include "UsersGroup.h"
using namespace serverMessage;


UsersGroup::UsersGroup(std::string &name)
{
    name_ = name;
    admin_ = nullptr;
}

User* UsersGroup::getUser(std::string &login)
{
    if (users_.count(login) != 0)
    {
        return users_[login];
    } else
    {
        return nullptr;
    }
}

std::string &UsersGroup::getName()
{
    return name_;
}

void UsersGroup::addUser(User* user)
{
    if (users_.size() == 0)
    {
        admin_ = user;
    }
    if (users_.count(user->getLogin()) == 0)
    {
        users_.insert({user->getLogin(), user});
    }
}

void UsersGroup::removeUser(std::string &login)
{
    if (users_.count(login) != 0)
    {
        users_.erase(login);
    }
    if (users_.size() == 0)
    {
        admin_ = nullptr;
    } else
    {
        admin_ = users_.begin()->second;
    }
}

Message UsersGroup::addMessage(std::string &message, User* user)
{
    Message newMessage(message, user);
    messages_.push_back(newMessage);
    return newMessage;
}

bool UsersGroup::containsUser(User *user)
{
    return users_.count(user->getLogin()) != 0;
}

bool UsersGroup::containsUser(std::string &userLogin)
{
    return users_.count(userLogin) != 0;
}

std::vector<std::string> UsersGroup::getUsers()
{
    std::vector<std::string> users;
    for (auto& u : users_)
    {
        users.push_back(u.first);
    }
    return users;
}

const std::vector<Message> &UsersGroup::getMessages()
{
    return messages_;
}

std::string UsersGroup::getAllMessages()
{
    std::stringstream ss;
    ss << "";

    qDebug() << messages_.size();

    for (Message& m : messages_)
    {
        ss << m.getMessageInfo() << "\n";
    }
    return ss.str();
}

void UsersGroup::deleteMessage(std::string& messageToDelete)
{
    int num = 0;
    for (Message m : messages_)
    {
        if (m.getMessageInfo() == messageToDelete)
        {
            messages_.erase(messages_.begin() + num);
            return;
        }
        num++;
    }
}
