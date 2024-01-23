#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "User.h"
#include <ctime>
#include <sstream>
#include <iomanip>

namespace serverMessage {

class Message
{
private:
    std::string text_;
    User* author_;
    tm* time_;
public:
    Message(std::string& text, User* user);

public:
    std::string& getText();

    User* getAuthor();

    tm* getTime();

    std::string getMessageInfo();
};
}
#endif // MESSAGE_H
