#include "PersonalCorrespondence.h"

PersonalCorrespondence::PersonalCorrespondence(User *user1, User *user2)
{
    user1_ = user1;
    user2_ = user2;
}

std::pair<User *, User *> PersonalCorrespondence::getUsers()
{
    return {user1_, user2_};
}

Message PersonalCorrespondence::addMessage(std::string &message, User *user)
{
    Message newMessage(message, user);
    messages_.push_back(newMessage);
    return newMessage;
}

std::string PersonalCorrespondence::getAllMessages()
{
    std::stringstream ss;
    for (Message& m : messages_)
    {
        ss << m.getMessageInfo() << "\n";
    }
    return ss.str();
}

void PersonalCorrespondence::deleteMessage(std::string &messageToDelete)
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
