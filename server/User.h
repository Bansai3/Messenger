#ifndef USER_H
#define USER_H
#include <string>

class User
{
public:
    User(
        std::string name,
        std::string surname,
        std::string login,
        std::string password
        );

    std::string& getName();
    std::string& getSurname();
    std::string& getLogin();
    std::string& getPassword();

    bool isSignedIn();
    void changeSignInState(bool newState);

private:
    std::string name_;
    std::string surname_;
    std::string login_;
    std::string password_;
    bool signedIn;
};

#endif // USER_H
