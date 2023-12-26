#include "Listener.h"
#include "Session.h"
#include <exception>

Listener::Listener(net::io_context &ioc, tcp::endpoint endpoint)
    : ioc_(ioc)
    , acceptor_(ioc)
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
    do_accept();
}

void Listener::sendToAll(beast::flat_buffer& message, std::shared_ptr<Session> sessionToIgnore)
{
    for(auto& session : sessions_)
    {
        if(session.get() != sessionToIgnore.get()) {
            session->writefromListener(message);
        }
    }
}

void Listener::closeSessions()
{
    for(auto& session : sessions_)
    {
        session->close();
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

void Listener::on_accept(beast::error_code ec, tcp::socket socket)
{
    if(ec)
    {
        fail(ec, "accept");
    }
    else
    {
        std::shared_ptr<Session> ptr = std::make_shared<Session>(std::move(socket), this);
        sessions_.push_back(ptr);
        ptr->run();
    }

    do_accept();
}

UsersStorage& Listener::getUsersStorage()
{
    return us_;
}
