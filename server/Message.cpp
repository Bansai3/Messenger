#include "Message.h"
using namespace serverMessage;

Message::Message(std::string &text, User *user)
{
    text_ = text;
    author_ = user;
    time_t now = time(0);
    time_ = localtime(&now);
}

std::string &Message::getText()
{
    return text_;
}

User *Message::getAuthor()
{
    return author_;
}

tm *Message::getTime()
{
    return time_;
}

std::string Message::getMessageInfo()
{
    std::string userLogin = author_->getLogin();
    std::string message = text_;
    std::stringstream ss;
    ss << std::put_time(time_, "%c");
    std::string timeValue = ss.str();
    return userLogin + ": " + message + " " + "(" + timeValue + ")";
}

