#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

typedef websocket::stream<beast::tcp_stream> ws;

#endif // NAMESPACES_H
