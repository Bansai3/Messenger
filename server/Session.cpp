#include "Session.h"
#include "Listener.h"

Session::Session(tcp::socket &&socket, Listener* listener)
    : ws_(std::move(socket)), listener_(listener){}

void Session::run()
{

    ws_.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::server));


    ws_.set_option(websocket::stream_base::decorator(
        [](websocket::response_type& res)
        {
            res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-async");
        }));


    ws_.async_accept(
        beast::bind_front_handler(
            &Session::on_accept,
            shared_from_this()));
}

void Session::on_accept(beast::error_code ec)
{
    if(ec) return fail(ec, "accept");

    do_read();
}

void Session::do_read()
{
    ws_.async_read(
        buffer_,
        beast::bind_front_handler(
            &Session::on_read,
            shared_from_this()));
}


void Session::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec == websocket::error::closed) return;

    if(ec) fail(ec, "read");

    handleRequest();
}

bool Session::checkJsonFormat(std::string reauestJson)
{
    std::stringstream ss(reauestJson);
    boost::property_tree::ptree tree;

    try
    {
        boost::property_tree::read_json(ss, tree);
        return true;
    } catch(const boost::property_tree::json_parser_error&)
    {
        return false;
    }
}

void Session::handleRequest()
{
    qDebug() << "start";

    std::string request(boost::asio::buffer_cast<const char*>(buffer_.data()), buffer_.size());
    std::stringstream ss(request);

    qDebug() << request;

    if (!checkJsonFormat(request))
    {
        handleInvalidRequest();
        return;
    }

    boost::property_tree::ptree tree;
    boost::property_tree::read_json(ss, tree);

    auto operationType = tree.get<std::string>("operation type");

    if (operationType == "sign in")
    {
        handleSignInRequest(tree);
    }
    else if (operationType == "sign up")
    {
        handleSignUpRequest(tree);
    }
    else if (operationType == "send message")
    {
        handleSendMessageRequest(tree);
    }
    else
    {
        handleInvalidRequest();
    }
}

void Session::handleSignInRequest(boost::property_tree::ptree& tree)
{
    qDebug() << "sign in";
    UsersStorage& us = listener_->getUsersStorage();

    std::string login = tree.get<std::string>("login");
    std::string password = tree.get<std::string>("password");

    boost::property_tree::ptree jsonResponse = us.getUser(login, password);

    sendResponse(jsonResponse);
}

void Session::handleSignUpRequest(boost::property_tree::ptree& tree)
{
    qDebug() << "sign up";
    UsersStorage& us = listener_->getUsersStorage();

    std::string login = tree.get<std::string>("login");
    std::string password = tree.get<std::string>("password");
    std::string name = tree.get<std::string>("name");
    std::string surname = tree.get<std::string>("surname");

    User user(name, surname, login, password);

    boost::property_tree::ptree jsonResponse = us.addUser(user);

    sendResponse(jsonResponse);
}

void Session::handleSendMessageRequest(boost::property_tree::ptree& tree)
{
    qDebug() << "handle message";
    std::string message = tree.get<std::string>("message");

    boost::beast::flat_buffer buffer;
    boost::asio::buffer_copy(buffer.prepare(message.size()), boost::asio::buffer(message));
    buffer.commit(message.size());

    listener_->sendToAll(buffer, shared_from_this());

    ws_.async_write(
        buffer.data(),
        beast::bind_front_handler(
            &Session::on_write,
            shared_from_this()));
}

void Session::handleInvalidRequest()
{
    boost::property_tree::ptree response;
    response.put("operation type", "bad request response");
    response.put("status", "ERROR");
    response.put("messsage", "Invalid request format");

    sendResponse(response);
}

void Session::sendResponse(boost::property_tree::ptree& jsonResponse)
{
    std::stringstream ss;
    boost::property_tree::write_json(ss, jsonResponse);
    std::string jsonStr = ss.str();

    qDebug() << jsonStr;

    boost::beast::flat_buffer buffer;
    auto os = boost::beast::ostream(buffer);
    write_json(os, jsonResponse, false);

    qDebug() << "response sended";

    ws_.async_write(
        buffer.data(),
        beast::bind_front_handler(
            &Session::on_write,
            shared_from_this()));
}

void Session::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec) return fail(ec, "write");

    buffer_.consume(buffer_.size());

    do_read();
}

ws& Session::getWebSocketStream()
{
    return ws_;
}

void Session::close()
{
    ws_.close(websocket::close_code::normal);
}

void Session::writefromListener(beast::flat_buffer& message)
{
    ws_.async_write(
        message.data(),
        beast::bind_front_handler(
            &Session::on_writefromListener,
            shared_from_this()));
}

void Session::on_writefromListener(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec) return fail(ec, "write");
}
