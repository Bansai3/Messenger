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

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

typedef websocket::stream<beast::tcp_stream> ws;

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
private:

    void handleRequest();

    void handleSignInRequest(boost::property_tree::ptree& tree);

    void handleSignUpRequest(boost::property_tree::ptree& tree);

    void handleSendMessageRequest(boost::property_tree::ptree& tree);

    void sendResponse(boost::property_tree::ptree& jsonResponse);

    bool checkJsonFormat(std::string reauestJson);

    void handleInvalidRequest();
};
#endif
