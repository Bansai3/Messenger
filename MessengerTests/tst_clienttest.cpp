#include <QtTest>
#include "sign_in.h"
#include "sign_up.h"
#include "chat.h"
#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

class ClientTest : public QObject
{
    Q_OBJECT

public:
    ClientTest();
    ~ClientTest();

private slots:
    void setMainWindowLabelTest();

    void changeSignInLineEditTest();

    void changeSignUpLineEditTest();

    void changeChatLineEditTest();

    void addMessagesToMessagesList();

    void addChatsToChatsList();
};

ClientTest::ClientTest(){}

ClientTest::~ClientTest(){}

void ClientTest::setMainWindowLabelTest()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    MainWindow mw;

    QLabel label;

    QString text_1 = "text";
    QString text_2 = "error";
    QString text_3 = "";

    mw.setLabelText(&label, text_1);
    QCOMPARE(label.text(), text_1);

    mw.setLabelText(&label, text_2);
    QCOMPARE(label.text(), text_2);

    mw.setLabelText(&label, text_3);
    QCOMPARE(label.text(), text_3);
}

void ClientTest::changeSignInLineEditTest()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    sign_in sn;

    QString login = "Login";
    QString password = "Password";

    sn.setLoginText(login);
    sn.setPasswordText(password);

    QString loginVal = sn.getLoginText();
    QString passwordVal = sn.getPasswordText();

    QCOMPARE(loginVal, login);
    QCOMPARE(passwordVal, password);
}

void ClientTest::changeSignUpLineEditTest()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    sign_up sn;

    QString login = "Login";
    QString password = "Password";
    QString name = "Name";
    QString surname = "Surname";


    sn.setLoginText(login);
    sn.setPasswordText(password);
    sn.setNameText(name);
    sn.setSurnameText(surname);

    QString loginVal = sn.getLoginText();
    QString passwordVal = sn.getPasswordText();
    QString nameVal = sn.getNameText();
    QString surnameVal = sn.getSurnameText();

    QCOMPARE(loginVal, login);
    QCOMPARE(passwordVal, password);
    QCOMPARE(nameVal, name);
    QCOMPARE(surnameVal, surname);
}

void ClientTest::changeChatLineEditTest()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    QString chatName = "chat";
    chat c(chatName);

    QString groupName = "group";
    QString message = "hello";

    c.setGroupNameText(groupName);
    c.setMessageText(message);

    QString groupNameVal = c.getGroupNameText();
    QString messageVal = c.getMessageText();

    QCOMPARE(groupNameVal, groupName);
    QCOMPARE(messageVal, message);
}

void ClientTest::addMessagesToMessagesList()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    QString chatName = "chat";

    QString message1 = "Hello";
    QString message2 = "there";


    chat c(chatName);

    c.addMessageToMessageList(message1);
    c.addMessageToMessageList(message2);

    auto messages = c.getMessagesFromMessageList();

    QCOMPARE(messages[0], message1);
    QCOMPARE(messages[1], message2);
}

void ClientTest::addChatsToChatsList()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    QString chatName = "chat";

    QString chat1 = "Group";
    QString chat2 = "Private Chat";

    chat c(chatName);

    c.addChatToChatList(chat1);
    c.addChatToChatList(chat2);

    auto chats = c.getChatsFromChatsList();

    QCOMPARE(chats[0], chat1);
    QCOMPARE(chats[1], chat2);
}



QTEST_APPLESS_MAIN(ClientTest)

#include "tst_clienttest.moc"
