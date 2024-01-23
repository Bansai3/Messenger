#include "User.h"

User::User(
    std::string name,
    std::string surname,
    std::string login,
    std::string password
    ):
    name_(name),
    surname_(surname),
    login_(login),
    password_(password),
    signedIn(false)
    {}

std::string& User::getName()
{
    return name_;
}
std::string& User::getSurname()
{
    return surname_;
}
std::string& User::getLogin()
{
    return login_;
}
std::string& User::getPassword()
{
    return password_;
}

bool User::isSignedIn()
{
    return signedIn;
}

void User::changeSignInState(bool newState)
{
    signedIn = newState;
}


