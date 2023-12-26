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

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

typedef websocket::stream<beast::tcp_stream> ws;

class Session;

class Listener : public std::enable_shared_from_this<Listener>,
                 public FailHandler
{
private:
    std::vector<std::shared_ptr<Session>> sessions_;
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    UsersStorage us_;

public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint);

    void run();

    void sendToAll(beast::flat_buffer& message, std::shared_ptr<Session> sessionToIgnore);

    void closeSessions();

    UsersStorage& getUsersStorage();

private:
    void do_accept();

    void on_accept(beast::error_code ec, tcp::socket socket);

    void sendToAllHandler(beast::error_code ec, std::size_t bytes_transferred);
};

#endif // LISTENER_H
