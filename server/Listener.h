#ifndef LISTENER_H
#define LISTENER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <QCoreApplication>
#include "FailHandler.h"
#include "UsersStorage.h"
#include <map>
#include "UsersGroup.h"
#include "PersonalCorrespondence.h"

class Session;
constexpr auto PING_INTERVAL = std::chrono::seconds{10};

class Listener : public std::enable_shared_from_this<Listener>,
                 public FailHandler
{
private:
    net::io_context& ioc_;
    tcp::acceptor acceptor_;

    UsersStorage us_;

    std::unordered_map<std::string, UsersGroup> groups_;
    std::unordered_map<std::string, PersonalCorrespondence> privateMessages_;
    std::unordered_map<std::string, std::shared_ptr<Session>> sessions_;
    boost::asio::steady_timer periodicTimer_;
    std::vector<std::shared_ptr<Session>> sessionsToDelete_;

public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint);

    void run();

    void closeSessions();

    UsersStorage& getUsersStorage();

    void sendMessageToAllGroupMembers(beast::flat_buffer &message, std::string& userLogin, std::string& groupName);

    void sendMessageToUser(beast::flat_buffer &message, std::string& userToSendLogin);

    void sendMessageToAllUsers(beast::flat_buffer &message, std::string& login);

    boost::property_tree::ptree addUsersGroup(std::string& name);

    boost::property_tree::ptree addPersonalCorrespondence(User* user1, User* user2);

    boost::property_tree::ptree addUserToGroup(std::string& groupName, User* user);

    boost::property_tree::ptree addMessageToGroup(std::string& groupName, std::string& message, User* user);

    boost::property_tree::ptree addMessageToPersonalCorrespondence(std::pair<User*, User*> users, std::string& message);

    boost::property_tree::ptree removeUserFromGroup(std::string& groupName, User* user);

    boost::property_tree::ptree deletePersonalCorrespondence(std::pair<User*, User*> users);

    boost::property_tree::ptree deleteMessageFromGroup(std::string& groupName, std::string& messageInfo, User* user);

    boost::property_tree::ptree deleteMessageFromPersonalCorrespondence(std::string& messageInfo,
                                                                        std::string& user1Login, std::string& user2Login);

    UsersGroup* getUsersGroup(std::string& groupName);

    std::string getAllGroupMessages(std::string& groupName);

    std::string getAllPrivateMessages(std::pair<User*, User*> users);

    std::string getAllChatsNames(std::string& chatToIgnore);

    bool checkGroupChat(std::string& groupName);

    bool checkPCChat(std::string& user1Login, std::string& user2Login);

    void addSession(std::string userLogin, std::shared_ptr<Session> session);

    net::io_context& getContext();

    void deleteSession(std::shared_ptr<Session> s);

    void addSessionToDelete(std::shared_ptr<Session> session);

    std::string findSession(std::shared_ptr<Session> session);

    PersonalCorrespondence *getPersonalCorrespondence(User* user1, User* user2);

private:
    void do_accept();

    void on_accept(beast::error_code ec, tcp::socket socket);

    void sendToAllHandler(beast::error_code ec, std::size_t bytes_transferred);

    void startPeriodicPinging();

    void sendPingPacket();
};

#endif // LISTENER_H
