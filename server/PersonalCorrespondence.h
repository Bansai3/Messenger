#ifndef PERSONALCORRESPONDENCE_H
#define PERSONALCORRESPONDENCE_H

#include "User.h"
#include "Message.h"
#include <sstream>
using namespace serverMessage;

class PersonalCorrespondence
{
private:
    User* user1_;
    User* user2_;
    std::vector<Message> messages_;
public:
    PersonalCorrespondence(User* user1, User* user2);

public:
    std::pair<User*, User*> getUsers();

    Message addMessage(std::string& message, User* user);

    std::string getAllMessages();

    void deleteMessage(std::string& messageToDelete);
};

#endif // PERSONALCORRESPONDENCE_H
