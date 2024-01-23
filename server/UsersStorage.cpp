 #include "UsersStorage.h"

boost::property_tree::ptree UsersStorage::addUser(User user)
{
    boost::property_tree::ptree response;

    response.put("operation type", "sign up response");

    if (!checkUserParameters(&user))
    {
        response.put("status", "ERROR");
        response.put("message", "Invalid user data format");
        return response;
    }

    std::string login = user.getLogin();

    bool loginExists = users_.count(login) != 0;

    if (loginExists)
    {
        response.put("operation type", "sign up response");
        response.put("status", "ERROR");
        response.put("message", "User with such login already exists");
    } else
    {
        users_.insert({login, user});
        response.put("status", "OK");
        response.put("message", "New user created");
    }

    return response;
}

boost::property_tree::ptree UsersStorage::getUser(std::string login, std::string password)
{
    boost::property_tree::ptree response;

    response.put("operation type", "sign in response");

    if (!checkLogin(login) || !checkPassword(password))
    {
        response.put("status", "ERROR");
        response.put("message", "Invalid login or password format");
        return response;
    }

    bool loginExists = users_.count(login) != 0;

    if (loginExists && users_.at(login).getPassword() == password)
    {
        response.put("status", "OK");
        response.put("message", "Login and password are correct");
    } else
    {
        response.put("status", "ERROR");
        response.put("message", "Login or password are incorrect");
    }
    return response;
}

User* UsersStorage::getUser(std::string &login)
{
    if (users_.count(login) == 0)
    {
        return nullptr;
    } else
    {
        return &users_.at(login);
    }
}

std::vector<std::string> UsersStorage::getUsers()
{
    std::vector<std::string> users;
    for (auto& u : users_)
    {
        users.push_back(u.first);
    }
    return users;
}

bool UsersStorage::checkUserParameters(User* user)
{
    std::string login = user->getLogin();
    std::string password = user->getPassword();
    std::string name = user->getName();
    std::string surname = user->getSurname();

    return checkLogin(login) &&
           checkPassword(password) &&
           checkName(name) &&
           checkSurname(surname);
}

bool UsersStorage::checkLogin(std::string login)
{
    if (login.size() < UserConstants::minLoginLen ||
        login.size() > UserConstants::maxLoginLen)
    {
        return false;
    }
    return checkAlphaAndDigitString(login);
}

bool UsersStorage::checkPassword(std::string password)
{
    if (password.size() < UserConstants::minPasswordLen ||
        password.size() > UserConstants::maxPasswordLen)
    {
        return false;
    }
    return checkAlphaAndDigitString(password);
}

bool UsersStorage::checkName(std::string name)
{
    if (name.size() < UserConstants::minNameLen ||
        name.size() > UserConstants::maxNameLen)
    {
        return false;
    }
    return checkAlphaString(name);
}

bool UsersStorage::checkSurname(std::string surname)
{
    if (surname.size() < UserConstants::minSurnameLen ||
        surname.size() > UserConstants::maxSurnameLen)
    {
        return false;
    }
    return checkAlphaString(surname);
}

bool UsersStorage::checkAlphaAndDigitString(std::string str)
{
    std::locale loc("en_US");

    bool containsAlpha = false;
    bool containsDigit = false;

    for (char c : str) {
        if (!std::isdigit(c, loc) && !std::isalpha(c, loc))
        {
            return false;
        }
        if (std::isdigit(c, loc))
        {
            containsDigit = true;
        }
        if (std::isalpha(c, loc))
        {
            containsAlpha = true;
        }
    }

    return containsAlpha && containsDigit;
}

bool UsersStorage::checkAlphaString(std::string str)
{
    std::locale loc("en_US");

    for (char c : str) {
        if (!std::isalpha(c, loc))
        {
            return false;
        }
    }

    return true;
}

