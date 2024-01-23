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
    else if (operationType == "create group")
    {
        handleCreateGroupRequest(tree);
    }
    else if (operationType == "start chat")
    {
        handleCreatePersonalCorrespondenceRequest(tree);
    }
    else if (operationType == "send message to group")
    {
        handleSendGroupMessageRequest(tree);
    }
    else if (operationType == "send message to pc")
    {
        handleSendPCMessageRequest(tree);
    }
    else if (operationType == "open group chat")
    {
        handleOpenGroupChatRequest(tree);
    }
    else if (operationType == "open private chat")
    {
        handleOpenPrivateChatRequest(tree);
    }
    else if (operationType == "leave group")
    {
        handleLeaveGroupRequest(tree);
    }
    else if (operationType == "end private chat")
    {
        handleEndPrivateChatRequest(tree);
    }
    else if (operationType == "join group")
    {
        handleJoinGroupRequest(tree);
    }
    else if (operationType == "delete message from group")
    {
        handleDeleteMessageFromGroupRequest(tree);
    }
    else if (operationType == "delete message from personal correspondence")
    {
        handleDeleteMessageFromPCRequest(tree);
    }
    else if(operationType == "get all chats")
    {
        handleGetAllChats(tree);
    }
    else if(operationType == "ping response")
    {
        qDebug() << "Ping Response";
        do_read();
    } else
    {
        handleInvalidRequest();
    }
}

void Session::handleSignInRequest(boost::property_tree::ptree& tree)
{
    qDebug() << "sign in";
    UsersStorage& us = listener_->getUsersStorage();

    std::vector<std::string> c = us.getUsers();
    for (auto& v : c)
    {
        qDebug() << v << "\n";
    }

    std::string login = tree.get<std::string>("login");
    std::string password = tree.get<std::string>("password");

    boost::property_tree::ptree jsonResponse = us.getUser(login, password);

    jsonResponse.put("user", login);

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

void Session::handleSendGroupMessageRequest(boost::property_tree::ptree& tree)
{
    qDebug() << "handle group message";

    std::string message = tree.get<std::string>("message");
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    std::string groupName = tree.get<std::string>("group");
    boost::property_tree::ptree pt = listener_->addMessageToGroup(groupName, message, user);

    listener_->addSession(login, shared_from_this());

    if (pt.get<std::string>("status") == "OK")
    {
        std::stringstream ss;
        boost::property_tree::write_json(ss, pt);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToAllGroupMembers(buffer, login, groupName);
    }

    sendResponse(pt);
}

void Session::handleSendPCMessageRequest(boost::property_tree::ptree &tree)
{
    qDebug() << "handle personal correspondence message";

    std::string message = tree.get<std::string>("message");
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    std::string userToSendLogin = tree.get<std::string>("user");
    User* userToSend = listener_->getUsersStorage().getUser(userToSendLogin);

    boost::property_tree::ptree pt = listener_->addMessageToPersonalCorrespondence({user, userToSend}, message);

    boost::property_tree::ptree ptForAnotherUser = pt;
    ptForAnotherUser.put("chat name", login);
    ptForAnotherUser.put("user who sent", userToSendLogin);

    if (pt.get<std::string>("status")== "OK")
    {
        std::stringstream ss;
        boost::property_tree::write_json(ss, ptForAnotherUser);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToUser(buffer, userToSendLogin);
    }

    sendResponse(pt);
}

void Session::handleCreateGroupRequest(boost::property_tree::ptree& tree)
{
    qDebug() << "create group";

    std::string groupName = tree.get<std::string>("name");
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree response;

    response.put("operation type", "create group response");

    boost::property_tree::ptree pt = listener_->addUsersGroup(groupName);
    UsersGroup* usersGroup = listener_->getUsersGroup(groupName);
    usersGroup->addUser(user);

    response.put("status", pt.get<std::string>("status"));
    response.put("message", pt.get<std::string>("message"));
    response.put("chat name", groupName);

    if (pt.get<std::string>("status") == "OK")
    {
        boost::property_tree::ptree newChatJson;

        newChatJson.put("operation type", "add new chat");
        newChatJson.put("status", "OK");
        newChatJson.put("message", groupName);
        newChatJson.put("chat type", "group");

        std::stringstream ss;
        boost::property_tree::write_json(ss, newChatJson);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToAllUsers(buffer, login);
    }

    sendResponse(response);
}

void Session::handleCreatePersonalCorrespondenceRequest(boost::property_tree::ptree &tree)
{
    qDebug() << "create personal correspondence";

    std::string login = tree.get<std::string>("user login");
    std::string user2Login = tree.get<std::string>("user");

    User* user = listener_->getUsersStorage().getUser(login);
    User* user2 = listener_->getUsersStorage().getUser(user2Login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree response;
    response.put("operation type", "create personal correspondence response");

    boost::property_tree::ptree tp = listener_->addPersonalCorrespondence(user, user2);

    response.put("status", tp.get<std::string>("status"));
    response.put("message", tp.get<std::string>("message"));
    response.put("chat name", user2Login);

    sendResponse(response);
}

void Session::handleOpenGroupChatRequest(boost::property_tree::ptree &tree)
{
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    std::string groupName = tree.get<std::string>("group");
    UsersGroup* usersGroup = listener_->getUsersGroup(groupName);

    boost::property_tree::ptree response;

    if (!usersGroup->containsUser(login))
    {
        response.put("operation type", "open group chat response");
        response.put("status", "ERROR");
        response.put("message", "User is not a member of the group!");
        response.put("chat name", groupName);
    } else
    {
        std::string allGroupMessages = listener_->getAllGroupMessages(groupName);

        qDebug() << "open group chat";

        response.put("operation type", "open group chat response");
        response.put("status", "OK");
        response.put("message", allGroupMessages);
        response.put("chat name", groupName);
    }

    sendResponse(response);
}

void Session::handleOpenPrivateChatRequest(boost::property_tree::ptree &tree)
{
    std::string userLogin = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(userLogin);

    listener_->addSession(userLogin, shared_from_this());

    std::string userToSendLogin = tree.get<std::string>("user");
    User* userToSend = listener_->getUsersStorage().getUser(userToSendLogin);

    boost::property_tree::ptree response;

    if (!listener_->checkPCChat(user->getLogin(), userToSend->getLogin()))
    {
        response.put("operation type", "open private chat response");
        response.put("status", "ERROR");
        response.put("message", "There is no chat between these users!");
    } else
    {
        std::string privateMessages = listener_->getAllPrivateMessages({user, userToSend});

        response.put("operation type", "open private chat response");
        response.put("status", "OK");
        response.put("message", privateMessages);
        response.put("chat name", userToSendLogin);
    }

    sendResponse(response);
}

void Session::handleLeaveGroupRequest(boost::property_tree::ptree &tree)
{
    std::string groupToLeaveName = tree.get<std::string>("group");
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree pt = listener_->removeUserFromGroup(groupToLeaveName, user);

    boost::property_tree::ptree response;
    response.put("operation type", "leave group response");
    response.put("status", pt.get<std::string>("status"));
    response.put("message", pt.get<std::string>("message"));
    response.put("chat name", groupToLeaveName);

    sendResponse(response);
}

void Session::handleEndPrivateChatRequest(boost::property_tree::ptree &tree)
{
    std::string userLogin = tree.get<std::string>("user login");
    std::string userToSendLogin = tree.get<std::string>("user");

    User* user = listener_->getUsersStorage().getUser(userLogin);
    User* userToSend = listener_->getUsersStorage().getUser(userToSendLogin);

    listener_->addSession(userLogin, shared_from_this());

    boost::property_tree::ptree pt = listener_->deletePersonalCorrespondence({user, userToSend});

    if (pt.get<std::string>("status") == "OK")
    {
        boost::property_tree::ptree responseToAnotherUser;

        responseToAnotherUser.put("operation type", "end private chat response");
        responseToAnotherUser.put("status", pt.get<std::string>("status"));
        responseToAnotherUser.put("message", pt.get<std::string>("message"));
        responseToAnotherUser.put("chat name", userLogin);
        responseToAnotherUser.put("user who sent", userToSendLogin);

        std::stringstream ss;
        boost::property_tree::write_json(ss, responseToAnotherUser);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToUser(buffer, userToSendLogin);
    }

    boost::property_tree::ptree response;
    response.put("operation type", "end private chat response");
    response.put("status", pt.get<std::string>("status"));
    response.put("message", pt.get<std::string>("message"));
    response.put("chat name", userToSendLogin);
    response.put("user who sent", userLogin);

    sendResponse(response);
}

void Session::handleJoinGroupRequest(boost::property_tree::ptree &tree)
{
    std::string groupName = tree.get<std::string>("group");
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree pt = listener_->addUserToGroup(groupName, user);

    boost::property_tree::ptree response;
    response.put("operation type", "join group response");
    response.put("status", pt.get<std::string>("status"));
    response.put("message", pt.get<std::string>("message"));

    sendResponse(response);
}

void Session::handleDeleteMessageFromGroupRequest(boost::property_tree::ptree &tree)
{
    std::string groupName = tree.get<std::string>("group");
    std::string messageInfo = tree.get<std::string>("message");
    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree pt = listener_->deleteMessageFromGroup(groupName, messageInfo, user);

    if (pt.get<std::string>("status") == "OK")
    {
        std::stringstream ss;
        boost::property_tree::write_json(ss, pt);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToAllGroupMembers(buffer, login, groupName);
    }

    sendResponse(pt);
}

void Session::handleDeleteMessageFromPCRequest(boost::property_tree::ptree &tree)
{
    std::string userLogin = tree.get<std::string>("user");
    std::string messageInfo = tree.get<std::string>("message");

    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree pt = listener_->deleteMessageFromPersonalCorrespondence(messageInfo,
                                                                                        user->getLogin(), userLogin);

    if (pt.get<std::string>("status") == "OK")
    {
        boost::property_tree::ptree responseToAnotherUser = pt;
        responseToAnotherUser.put("chat name", login);
        responseToAnotherUser.put("user who sent", userLogin);

        std::stringstream ss;
        boost::property_tree::write_json(ss, responseToAnotherUser);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToUser(buffer, userLogin);
    }

    sendResponse(pt);
}

void Session::handleGetAllChats(boost::property_tree::ptree &tree)
{

    std::string login = tree.get<std::string>("user login");
    User* user = listener_->getUsersStorage().getUser(login);

    listener_->addSession(login, shared_from_this());

    boost::property_tree::ptree response;
    std::string chatsNames = listener_->getAllChatsNames(login);

    qDebug() << "chatsNames" << chatsNames << "\n";

    if (!user->isSignedIn())
    {
        user->changeSignInState(true);

        boost::property_tree::ptree newChatJson;

        newChatJson.put("operation type", "add new chat");
        newChatJson.put("status", "OK");
        newChatJson.put("message", login);
        newChatJson.put("chat type", "private chat");

        std::stringstream ss;
        boost::property_tree::write_json(ss, newChatJson);

        std::string messageJson = ss.str();

        boost::beast::flat_buffer buffer;
        boost::asio::buffer_copy(buffer.prepare(messageJson.size()), boost::asio::buffer(messageJson));
        buffer.commit(messageJson.size());

        listener_->sendMessageToAllUsers(buffer, login);
    }

    response.put("operation type", "get all chats response");
    response.put("status", "OK");
    response.put("message", chatsNames);
    response.put("user", login);

    sendResponse(response);
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

void Session::ping(beast::flat_buffer &fb)
{
    ws_.async_write(
        fb.data(),
        beast::bind_front_handler(
            &Session::handlePing,
            shared_from_this()));
}

void Session::handlePing(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec) {
        qDebug() << "Ping ERROR!";
        listener_->addSessionToDelete(shared_from_this());
    }
}
