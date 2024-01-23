#include "Listener.h"
#include "Session.h"
#include <exception>

Listener::Listener(net::io_context &ioc, tcp::endpoint endpoint)
    : ioc_(ioc)
    , acceptor_(ioc),
    periodicTimer_(ioc)
{
    beast::error_code ec;


    acceptor_.open(endpoint.protocol(), ec);
    if(ec)
    {
        fail(ec, "open");
        return;
    }


    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if(ec)
    {
        fail(ec, "set_option");
        return;
    }


    acceptor_.bind(endpoint, ec);
    if(ec)
    {
        fail(ec, "bind");
        return;
    }


    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if(ec)
    {
        fail(ec, "listen");
        return;
    }
}

void Listener::run()
{
    startPeriodicPinging();
    do_accept();
}

void Listener::sendMessageToAllGroupMembers(beast::flat_buffer &message, std::string& userLogin, std::string& groupName)
{
    UsersGroup* usersGroup = &groups_.at(groupName);
    std::vector<std::string> usrs = usersGroup->getUsers();
    for(auto& u : usrs)
    {
        qDebug() << u << "\n";
    }

    for(auto& session : sessions_)
    {
        std::string userL = session.first;
        qDebug() << userL;
        if((session.first != userLogin) && usersGroup->containsUser(userL))
        {
            qDebug() << "Message send to user " + session.first << "\n";
            session.second->writefromListener(message);
        }
    }
}

void Listener::sendMessageToUser(beast::flat_buffer &message, std::string& userToSendLogin)
{
    qDebug() << "Sending message to user..." << "\n";
    qDebug() << "User to send login" << userToSendLogin << "\n";
    for(auto& session : sessions_)
    {
        qDebug() << session.first << "\n";
        if(session.first == userToSendLogin) {
            session.second->writefromListener(message);
            return;
        }
    }
}

void Listener::sendMessageToAllUsers(beast::flat_buffer &message, std::string& login)
{
    qDebug() << "sessions size" << sessions_.size();
    qDebug() << "login" << login;
    for(auto& session : sessions_)
    {
        qDebug() << session.first;
        if(session.first != login) {
            qDebug() << "Hello";
            session.second->writefromListener(message);
        }
    }
}

void Listener::closeSessions()
{
    for(auto& session : sessions_)
    {
        session.second->close();
    }
    acceptor_.close();
}


void Listener::do_accept()
{
    acceptor_.async_accept(
        net::make_strand(ioc_),
        beast::bind_front_handler(
            &Listener::on_accept,
            shared_from_this()));
}


void Listener::sendToAllHandler(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec) return fail(ec, "write");
}

void Listener::deleteSession(std::shared_ptr<Session> s)
{
    std::string sessionUserLogin;
    for (auto& session : sessions_)
    {
        if (session.second == s)
        {
            sessionUserLogin = session.first;
        }
    }
    if (sessions_.count(sessionUserLogin) != 0)
    {
        sessions_.erase(sessionUserLogin);
    }
}

void Listener::addSessionToDelete(std::shared_ptr<Session> session)
{
    sessionsToDelete_.push_back(session);
}

std::string Listener::findSession(std::shared_ptr<Session> session)
{
    for(auto& s : sessions_)
    {
        if(s.second == session)
        {
            return s.first;
        }
    }
    return "";
}

PersonalCorrespondence *Listener::getPersonalCorrespondence(User *user1, User *user2)
{
    std::string usersLogins1 = user1->getLogin() + " " + user2->getLogin();
    std::string usersLogins2 = user2->getLogin() + " " + user1->getLogin();
    if(privateMessages_.count(usersLogins1) == 0 && privateMessages_.count(usersLogins2) == 0)
    {
        return nullptr;
    } else
    {
        if(privateMessages_.count(usersLogins1) != 0)
        {
            return &privateMessages_.at(usersLogins1);
        } else {
            return &privateMessages_.at(usersLogins2);
        }
    }
}

boost::property_tree::ptree Listener::addUsersGroup(std::string &name)
{
    boost::property_tree::ptree response;
    response.put("operation type", "add group response");

    if (groups_.count(name) != 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Group with the name " + name + " already exists!");
    }
    else
    {
        UsersGroup usersGroup(name);
        groups_.insert({name, usersGroup});
        response.put("status", "OK");
        response.put("message", "Group " + name + " created!");
    }

    return response;
}

boost::property_tree::ptree Listener::addPersonalCorrespondence(User *user1, User *user2)
{
    std::string usersPair = user1->getLogin() + " " + user2->getLogin();
    std::string usersPair2 = user2->getLogin() + " " + user1->getLogin();

    boost::property_tree::ptree response;
    response.put("operation type", "add personal correspondence response");

    if (privateMessages_.count(usersPair) != 0 || privateMessages_.count(usersPair2) != 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Personal correspondence already exists!");
    }
    else
    {
        PersonalCorrespondence pc(user1, user2);
        privateMessages_.insert({usersPair, pc});
        response.put("status", "OK");
        response.put("message", "Personal correspondence created!");
    }

    return response;
}

boost::property_tree::ptree Listener::addUserToGroup(std::string &groupName, User *user)
{
    boost::property_tree::ptree response;
    response.put("operation type", "add user to group response");

    if (groups_.count(groupName) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Group with the name " + groupName + " does not exist!");
    }
    else
    {
        UsersGroup* group = &groups_.at(groupName);
        if (group->containsUser(user))
        {
            response.put("status", "ERROR");
            response.put("message", "User already is a member of the group!");
        } else
        {
            group->addUser(user);
            response.put("status", "OK");
            response.put("message", "User added to the group");
        }
    }
    return response;
}

boost::property_tree::ptree Listener::addMessageToGroup(std::string &groupName, std::string& message, User* user)
{
    boost::property_tree::ptree response;
    response.put("operation type", "add message to group response");

    if (groups_.count(groupName) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Group with the name " + groupName + " does not exist!");
    }
    else
    {
        UsersGroup* group = &groups_.at(groupName);
        Message m = group->addMessage(message, user);
        response.put("status", "OK");
        response.put("message", m.getMessageInfo());
        response.put("chat name", groupName);
    }

    return response;
}

boost::property_tree::ptree Listener::addMessageToPersonalCorrespondence(std::pair<User*, User*> users,
                                                                          std::string& message)
{
    std::string usersPair = users.first->getLogin() + " " + users.second->getLogin();
    std::string usersPair2 = users.second->getLogin() + " " + users.first->getLogin();

    boost::property_tree::ptree response;
    response.put("operation type", "add message to personal correspondence response");

    if (privateMessages_.count(usersPair) == 0 && privateMessages_.count(usersPair2) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Users does not have personal correspondence!");
    }
    else
    {
        std::string usersPairName;
        if (privateMessages_.count(usersPair) != 0)
        {
            usersPairName = usersPair;
        } else
        {
            usersPairName = usersPair2;
        }
        PersonalCorrespondence* pc = &privateMessages_.at(usersPairName);
        Message m = pc->addMessage(message, users.first);
        response.put("status", "OK");
        response.put("message", m.getMessageInfo());
        response.put("chat name", users.second->getLogin());
        response.put("user who sent", users.first->getLogin());
    }

    return response;
}

boost::property_tree::ptree Listener::removeUserFromGroup(std::string &groupName, User *user)
{
    boost::property_tree::ptree response;
    response.put("operation type", "remove user from the group");

    if (groups_.count(groupName) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Group with the name " + groupName + " does not exist!");
    }
    else
    {
        UsersGroup* group = &groups_.at(groupName);
        group->removeUser(user->getLogin());
        response.put("status", "OK");
        response.put("message", "User removed from the group");
    }

    return response;
}

boost::property_tree::ptree Listener::deletePersonalCorrespondence(std::pair<User*, User*> users)
{
    std::string usersPair = users.first->getLogin() + " " + users.second->getLogin();
    std::string usersPair2 = users.second->getLogin() + " " + users.first->getLogin();

    boost::property_tree::ptree response;
    response.put("operation type", "delete personal correspondence response");

    if (privateMessages_.count(usersPair) == 0 && privateMessages_.count(usersPair2) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Personal correspondence does not exist!");
    }
    else
    {
        std::string usersPairName;
        if (privateMessages_.count(usersPair) != 0)
        {
            usersPairName = usersPair;
        } else
        {
            usersPairName = usersPair2;
        }
        privateMessages_.erase(usersPairName);
        response.put("status", "OK");
        response.put("message", "Personal correspondence deleted!");
    }

    return response;
}

boost::property_tree::ptree Listener::deleteMessageFromGroup(std::string &groupName, std::string &messageInfo, User* user)
{
    boost::property_tree::ptree response;
    response.put("operation type", "delete message from group response");

    std::string authorLogin = messageInfo.substr(0, messageInfo.find(":"));

    if (authorLogin != user->getLogin())
    {
        response.put("status", "ERROR");
        response.put("message", "User can not delete other users messages!");
        return response;
    }

    if (groups_.count(groupName) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Group does not exist!");
    }
    else
    {
        UsersGroup* ug = &groups_.at(groupName);
        ug->deleteMessage(messageInfo);
        std::string allMessages = ug->getAllMessages();
        response.put("status", "OK");
        response.put("message", allMessages);
        response.put("chat name", groupName);
    }

    return response;
}

boost::property_tree::ptree Listener::deleteMessageFromPersonalCorrespondence(std::string& messageInfo,
                                                                              std::string& user1Login, std::string& user2Login)
{
    boost::property_tree::ptree response;
    response.put("operation type", "delete message from personal correspondence");

    std::string authorLogin = messageInfo.substr(0, messageInfo.find(":"));
    std::string usersPair = user1Login + " " + user2Login;
    std::string usersPair2 = user2Login + " " + user1Login;

    if (authorLogin != user1Login)
    {
        response.put("status", "ERROR");
        response.put("message", "User can not delete other users messages!");
        return response;
    }

    if (privateMessages_.count(usersPair) == 0 && privateMessages_.count(usersPair2) == 0)
    {
        response.put("status", "ERROR");
        response.put("message", "Group does not exist!");
    }
    else
    {
        std::string usersPairName;
        if(privateMessages_.count(usersPair) != 0)
        {
            usersPairName = usersPair;
        } else
        {
            usersPairName = usersPair2;
        }
        PersonalCorrespondence* pc = &privateMessages_.at(usersPairName);
        pc->deleteMessage(messageInfo);
        std::string allMessages = pc->getAllMessages();
        response.put("status", "OK");
        response.put("message", allMessages);
        response.put("chat name", user2Login);
        response.put("user who sent", user1Login);
    }

    return response;
}

UsersGroup *Listener::getUsersGroup(std::string &groupName)
{
    if (groups_.count(groupName) != 0)
    {
        return &groups_.at(groupName);
    }
    return nullptr;
}

std::string Listener::getAllGroupMessages(std::string& groupName)
{
    if (groups_.count(groupName) == 0)
    {
        return "";
    }
    UsersGroup* usersGroup = &groups_.at(groupName);
    qDebug() << "Get Users groups";
    return usersGroup->getAllMessages();
}

std::string Listener::getAllPrivateMessages(std::pair<User *, User *> users)
{
    std::string usersPair = users.first->getLogin() + " " + users.second->getLogin();
    std::string usersPair2 = users.second->getLogin() + " " + users.first->getLogin();

    if (privateMessages_.count(usersPair) == 0 && privateMessages_.count(usersPair2) == 0 )
    {
        return "";
    }
    std::string usersPairName;
    if (privateMessages_.count(usersPair) != 0)
    {
        usersPairName = usersPair;
    } else
    {
        usersPairName = usersPair2;
    }
    PersonalCorrespondence* pc = &privateMessages_.at(usersPairName);
    return pc->getAllMessages();
}

std::string Listener::getAllChatsNames(std::string& chatToIgnore)
{
    std::unordered_map<std::string, bool> chats;
    std::vector<std::string> users = us_.getUsers();

    for (auto& chat : groups_)
    {
        if (chats.count(chat.first + "(group)") == 0)
        {
            chats.insert({chat.first + "(group)", true});
        }
    }

    for (auto& session : sessions_)
    {
        if (chats.count(session.first + "(private chat)") == 0)
        {
            chats.insert({session.first + "(private chat)", true});
        }
    }

    std::string chatsList = "";
    for (auto& chat : chats)
    {
        if (chat.first == chatToIgnore + "(private chat)") continue;
        chatsList += chat.first + "\n";
    }

    int posToDelete = chatsList.rfind('\n');
    if (posToDelete != std::string::npos) {
        chatsList.erase(posToDelete, 1);
    }
    return chatsList;
}

bool Listener::checkGroupChat(std::string &chatName)
{
    return groups_.count(chatName) != 0;
}

bool Listener::checkPCChat(std::string& user1Login, std::string& user2Login)
{
    std::string usersPair = user1Login + " " + user2Login;
    std::string usersPair2 = user2Login + " " + user1Login;

    return privateMessages_.count(usersPair) != 0 || privateMessages_.count(usersPair2) != 0;
}

void Listener::addSession(std::string userLogin, std::shared_ptr<Session> session)
{
    if (sessions_.count(userLogin) != 0)
    {
        sessions_[userLogin] = session;
    } else
    {
        sessions_.insert({userLogin, session});
    }
}

boost::asio::io_context &Listener::getContext()
{
    return ioc_;
}

void Listener::on_accept(beast::error_code ec, tcp::socket socket)
{
    if(ec)
    {
        fail(ec, "accept");
    }
    else
    {
        auto session = std::make_shared<Session>(std::move(socket), this);
        session->run();
    }

    do_accept();
}

UsersStorage& Listener::getUsersStorage()
{
    return us_;
}

void Listener::startPeriodicPinging()
{
    periodicTimer_.expires_from_now(PING_INTERVAL);
    periodicTimer_.async_wait(bind(&Listener::sendPingPacket, this));
}


void Listener::sendPingPacket()
{
    boost::property_tree::ptree packet;


    packet.put("operation type", "ping");
    packet.put("status", "OK");
    packet.put("message", "ping client");

    boost::beast::flat_buffer buffer;
    auto os = boost::beast::ostream(buffer);
    write_json(os, packet, false);

    for (auto& session : sessions_)
    {
        qDebug() << "Ping client";
        session.second->ping(buffer);
    }

    for (auto& sesssion : sessionsToDelete_)
    {
        std::string val = findSession(sesssion);
        if (val != "")
        {
            qDebug() << "Simialr sessions!";
            std::shared_ptr<Session> s = sessions_.at(val);
            sessions_.erase(val);
        }
    }

    sessionsToDelete_.clear();

    periodicTimer_.expires_from_now(PING_INTERVAL);
    periodicTimer_.async_wait(bind(&Listener::sendPingPacket, this));
}
