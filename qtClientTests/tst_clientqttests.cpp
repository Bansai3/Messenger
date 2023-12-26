#include <QtTest>
#include "sign_in.h"
#include "sign_up.h"
#include "chat.h"
#include "mainwindow.h"
#include "UsersStorage.h"
#include <QApplication>
#include <QLabel>

class clientAndServerQtTests : public QObject
{
    Q_OBJECT

public:
    clientAndServerQtTests();
    ~clientAndServerQtTests();

private slots:
    void setMainWindowLabelTest();

    void changeSignInLineEditTest();

    void changeSignUpLineEditTest();

    void changeChatLineEditTest();

    void addUserToUsersStorage();

    void getUserFromUserStorage();

    void addIncorrectDataUser();
};

clientAndServerQtTests::clientAndServerQtTests(){}

clientAndServerQtTests::~clientAndServerQtTests(){}

void clientAndServerQtTests::setMainWindowLabelTest()
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

void clientAndServerQtTests::changeSignInLineEditTest()
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

void clientAndServerQtTests::changeSignUpLineEditTest()
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

void clientAndServerQtTests::changeChatLineEditTest()
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    chat c;

    QString ip = "127.0.0.1";
    QString message = "hello";

    c.setIpText(ip);
    c.setMessageText(message);

    QString ipVal = c.getIpText();
    QString messageVal = c.getMessageText();

    QCOMPARE(ipVal, ip);
    QCOMPARE(messageVal, message);
}

void clientAndServerQtTests::addUserToUsersStorage()
{
    UsersStorage us;

    std::string status = "OK";
    std::string message = "New user created";

    std::string name = "Vladislav";
    std::string surname = "Harlamovich";
    std::string login = "HelloThere222";
    std::string password = "234567yrtr";
    User u(name, surname, login, password);

    boost::property_tree::ptree json = us.addUser(u);
    auto resStatus = json.get<std::string>("status");
    auto resMessage = json.get<std::string>("message");

    QCOMPARE(resStatus, status);
    QCOMPARE(resMessage, message);
}

void clientAndServerQtTests::getUserFromUserStorage()
{
    UsersStorage us;

    std::string status = "OK";
    std::string message = "Login and password are correct";

    std::string name = "Vladislav";
    std::string surname = "Harlamovich";
    std::string login = "HelloThere222";
    std::string password = "234567yrtr";
    User u(name, surname, login, password);

    boost::property_tree::ptree json = us.addUser(u);

    boost::property_tree::ptree getUserJson = us.getUser(login, password);

    auto resStatus = getUserJson.get<std::string>("status");
    auto resMessage = getUserJson.get<std::string>("message");

    QCOMPARE(resStatus, status);
    QCOMPARE(resMessage, message);
}

void clientAndServerQtTests::addIncorrectDataUser()
{
    UsersStorage us;

    std::string status = "ERROR";
    std::string message = "Invalid user data format";

    std::string name = "Vladislav";
    std::string surname = "Harlamovich";
    std::string login = "rrr...";
    std::string password = "...";
    User u(name, surname, login, password);

    boost::property_tree::ptree json = us.addUser(u);
    auto resStatus = json.get<std::string>("status");
    auto resMessage = json.get<std::string>("message");

    QCOMPARE(resStatus, status);
    QCOMPARE(resMessage, message);
}

QTEST_APPLESS_MAIN(clientAndServerQtTests)

#include "tst_clientqttests.moc"
