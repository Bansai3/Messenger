#ifndef SESSION_H
#define SESSION_H

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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Namespaces.h"
#include "User.h"

class Listener;

class Session : public std::enable_shared_from_this<Session>,
                public FailHandler
{
private:
    ws ws_;
    beast::flat_buffer buffer_;
    Listener* listener_;

public:
    explicit Session(tcp::socket&& socket, Listener* listener);

    void run();

    void on_accept(beast::error_code ec);

    void do_read();

    void on_read(beast::error_code ec, std::size_t bytes_transferred);

    void on_write(beast::error_code ec, std::size_t bytes_transferred);

    ws& getWebSocketStream();

    void close();

    void writefromListener(beast::flat_buffer& message);

    void on_writefromListener(beast::error_code ec, std::size_t bytes_transferred);

    void ping(boost::beast::flat_buffer& fb);

    void handlePing(beast::error_code ec, std::size_t bytes_transferred);

private:

    void handleRequest();

    void handleSignInRequest(boost::property_tree::ptree& tree);

    void handleSignUpRequest(boost::property_tree::ptree& tree);

    void handleSendGroupMessageRequest(boost::property_tree::ptree& tree);

    void handleSendPCMessageRequest(boost::property_tree::ptree& tree);

    void sendResponse(boost::property_tree::ptree& jsonResponse);

    bool checkJsonFormat(std::string reauestJson);

    void handleInvalidRequest();

    void handleCreateGroupRequest(boost::property_tree::ptree& tree);

    void handleCreatePersonalCorrespondenceRequest(boost::property_tree::ptree& tree);

    void handleOpenGroupChatRequest(boost::property_tree::ptree& tree);

    void handleOpenPrivateChatRequest(boost::property_tree::ptree& tree);

    void handleLeaveGroupRequest(boost::property_tree::ptree& tree);

    void handleEndPrivateChatRequest(boost::property_tree::ptree& tree);

    void handleJoinGroupRequest(boost::property_tree::ptree& tree);

    void handleDeleteMessageFromGroupRequest(boost::property_tree::ptree& tree);

    void handleDeleteMessageFromPCRequest(boost::property_tree::ptree &tree);

    void handleGetAllChats(boost::property_tree::ptree &tree);
};
#endif
