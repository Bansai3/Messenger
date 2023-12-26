#ifndef FAILHANDLER_H
#define FAILHANDLER_H
#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>

namespace beast = boost::beast;

class FailHandler {
public:
    void fail(beast::error_code ec, char const* what);
};

#endif // FAILHANDLER_H
