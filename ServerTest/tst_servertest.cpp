#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "Listener.h"

using namespace testing;

TEST(ListenerTest, AddUsersGroup)
{
    const auto port = 8001;
    const auto threads = 1;

    auto ep = tcp::endpoint(tcp::v4(), port);
    net::io_context ioc;

    Listener listener(ioc, ep);

    std::string groupName = "Group";

    listener.addUsersGroup(groupName);

    UsersGroup* usersGroup = listener.getUsersGroup(groupName);

    ASSERT_EQ(groupName, usersGroup->getName());
}

TEST(ListenerTest, AddPersonalCorrespondence)
{
    const auto port = 8001;
    const auto threads = 1;

    auto ep = tcp::endpoint(tcp::v4(), port);
    net::io_context ioc;

    Listener listener(ioc, ep);

    User user1("Tom", "James", "Bear1", "123dfrgv");
    User user2("Bane", "James", "Bear2", "2323hghcu");

    std::string usersLogins1 = user1.getLogin() + " " + user2.getLogin();
    std::string usersLogins2 = user2.getLogin() + " " + user1.getLogin();

    listener.addPersonalCorrespondence(&user1, &user2);

    PersonalCorrespondence* pc = listener.getPersonalCorrespondence(&user1, &user2);

    auto users = pc->getUsers();

    std::string usersLoginsValues = users.first->getLogin() + " " + users.second->getLogin();

    ASSERT_TRUE(usersLoginsValues == usersLogins2 ||usersLoginsValues == usersLogins1);
}

TEST(ListenerTest, AddUserToGroup)
{
    const auto port = 8001;
    const auto threads = 1;

    auto ep = tcp::endpoint(tcp::v4(), port);
    net::io_context ioc;

    Listener listener(ioc, ep);

    std::string groupName = "Group";

    listener.addUsersGroup(groupName);

    User user1("Tom", "James", "Bear1", "123dfrgv");

    listener.addUserToGroup(groupName, &user1);

    UsersGroup* ug = listener.getUsersGroup(groupName);

    ASSERT_TRUE(ug->containsUser(user1.getLogin()));
}

TEST(ListenerTest, AddMessageToGroup)
{
    const auto port = 8001;
    const auto threads = 1;

    auto ep = tcp::endpoint(tcp::v4(), port);
    net::io_context ioc;

    Listener listener(ioc, ep);

    std::string groupName = "Group";

    listener.addUsersGroup(groupName);

    User user1("Tom", "James", "Bear1", "123dfrgv");

    std::string message = "Hi everyone!";

    listener.addMessageToGroup(groupName, message, &user1);

    UsersGroup* ug = listener.getUsersGroup(groupName);

    std::vector<serverMessage::Message> allGroupMessages = ug->getMessages();

    ASSERT_EQ(message, allGroupMessages[0].getText());
}

TEST(ListenerTest, removeUserFromGroup)
{
    const auto port = 8001;
    const auto threads = 1;

    auto ep = tcp::endpoint(tcp::v4(), port);
    net::io_context ioc;

    Listener listener(ioc, ep);

    std::string groupName = "Group";

    listener.addUsersGroup(groupName);

    User user1("Tom", "James", "Bear1", "123dfrgv");

    listener.addUserToGroup(groupName, &user1);

    listener.removeUserFromGroup(groupName, &user1);

    UsersGroup* ug = listener.getUsersGroup(groupName);

    ASSERT_TRUE(ug->containsUser(user1.getLogin()) == false);
}

