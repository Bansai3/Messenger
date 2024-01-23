#include "chat.h"
#include "ui_chat.h"

chat::chat(QString& userLogin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat),
    userLogin_(userLogin)
{
    ui->setupUi(this);
    QPixmap image("/Users/Vadim/Desktop/ITMO/5_сем/Продвинутый_c++/course_project/images/back_ground_3.jpeg");
    ui->background_image->setPixmap(image.scaled(1500, 1500, Qt::KeepAspectRatio));
    connectToDevice();
    setDeviceContoller();
    setButtonsState(false);
}

void chat::setUserLogin(QString &userLogin)
{
    userLogin_ = userLogin;
}

chat::~chat()
{
    delete ui;
}

void chat::setDeviceContoller()
{
    connect(&_controller, &DeviceController::errorOccurred, this, &chat::device_errorOccurred);
    connect(&_controller, &DeviceController::dataReady, this, &chat::device_dataReady);
}

void chat::sendMessage(QJsonObject &json)
{
    QJsonDocument jsonDoc(json);
    QString message = jsonDoc.toJson();

    _controller.send(message);
}

void chat::setButtonsState(bool state)
{
    ui->deleteChatButton->setEnabled(state);
    ui->joinGroupButton->setEnabled(state);
    ui->leaveGroupButton->setEnabled(state);
    ui->openButton->setEnabled(state);
    ui->createGroupButton->setEnabled(state);
    ui->createGroupButton->setEnabled(state);
    ui->groupNameLineEdit->setEnabled(state);
    ui->startChatButton->setEnabled(state);
    ui->deleteMessageButton->setEnabled(state);
    ui->messageLineEdit->setEnabled(state);
    ui->sendMessageButton->setEnabled(state);
}

void chat::setButtonsHoverState()
{
    QString style = "QPushButton:hover {"
                    "background-color: rgb(187, 253, 255);"
                    "}";
    ui->deleteChatButton->setStyleSheet(style);
    ui->joinGroupButton->setStyleSheet(style);
    ui->leaveGroupButton->setStyleSheet(style);
    ui->openButton->setStyleSheet(style);
    ui->createGroupButton->setStyleSheet(style);
    ui->createGroupButton->setStyleSheet(style);
    ui->startChatButton->setStyleSheet(style);
}

void chat::sendPingResponse()
{
    qDebug() << "Send ping response";

    QJsonObject json;

    json["operation type"] = "ping response";

    sendMessage(json);
}

std::pair<QString, QString> chat::getChatNameAndType(QString &chatTitle)
{
    if (chatTitle == "None")
    {
        return {"None", "None"};
    }
    int chatTypeStart = chatTitle.indexOf("(");
    int chatTypeEnd = chatTitle.indexOf(")");
    int chatTypeSize = chatTypeEnd - chatTypeStart - 1;
    int chatNameSize = chatTypeStart;

    QString chatType = chatTitle.mid(chatTypeStart + 1, chatTypeSize);
    QString chatName = chatTitle.mid(0, chatNameSize);

    return {chatName, chatType};
}

void chat::handleResponse(QJsonObject &jsonResponse)
{
    QString operationType = jsonResponse["operation type"].toString();
    QString status = jsonResponse["status"].toString();
    QString message = jsonResponse["message"].toString();

    qDebug() << "Message" << message;

    if (status == "ERROR")
    {
        (new QErrorMessage(this))->showMessage(message);
    }
    else
    {
        if (operationType == "open private chat response")
        {
            if (ui->chatTitle->text() != jsonResponse["chat name"].toString() + "(private chat)")
            {
                ui->messagesListWidget->clear();
                if (message != "")
                {
                    char delimiter = '\n';
                    std::istringstream ss(message.toStdString());
                    std::string token;
                    while (std::getline(ss, token, delimiter)) {
                        ui->messagesListWidget->addItem(QString::fromStdString(token));
                    }
                }
                ui->chatTitle->setText(jsonResponse["chat name"].toString() + "(private chat)");
            }
        }
        else if (operationType == "open group chat response")
        {
            if (ui->chatTitle->text() != jsonResponse["chat name"].toString() + "(group)")
            {
                ui->messagesListWidget->clear();
                if (message != "")
                {
                    char delimiter = '\n';
                    std::istringstream ss(message.toStdString());
                    std::string token;
                    while (std::getline(ss, token, delimiter)) {
                        ui->messagesListWidget->addItem(QString::fromStdString(token));
                    }
                }
                ui->chatTitle->setText(jsonResponse["chat name"].toString() + "(group)");
            }
        }
        else if (operationType == "join group response")
        {
            showInformationBox(message);
        } else if (operationType == "end private chat response")
        {
            if (ui->chatTitle->text() == jsonResponse["chat name"].toString() + "(private chat)"
                && userLogin_ == jsonResponse["user who sent"].toString())
            {
                ui->messagesListWidget->clear();
                ui->chatTitle->setText("None");
            }
            showInformationBox(message);
        } else if (operationType == "leave group response")
        {
            if (ui->chatTitle->text() == jsonResponse["chat name"].toString() + "(group)")
            {
                ui->messagesListWidget->clear();
                ui->chatTitle->setText("None");
            }
            showInformationBox(message);
        } else if (operationType == "create group response")
        {
            ui->chatsListWidget->addItem(jsonResponse["chat name"].toString() + QString("(group)"));
            showInformationBox(message);
        } else if (operationType == "create personal correspondence response")
        {
            showInformationBox(message);
        } else if (operationType == "add message to group response")
        {
            qDebug() << ui->chatTitle->text();
            qDebug() << jsonResponse["chat name"].toString() + "(group)";
            if (ui->chatTitle->text() == jsonResponse["chat name"].toString() + "(group)")
            {
                ui->messagesListWidget->addItem(message);
            }
        } else if (operationType == "add message to personal correspondence response")
        {
            if (ui->chatTitle->text() == jsonResponse["chat name"].toString() + "(private chat)" &&
                userLogin_ == jsonResponse["user who sent"].toString())
            {
                ui->messagesListWidget->addItem(message);
            }
        } else if (operationType == "delete message from group response")
        {
            if (ui->chatTitle->text() == jsonResponse["chat name"].toString() + "(group)")
            {
                ui->messagesListWidget->clear();
                if (message != "")
                {
                    char delimiter = '\n';
                    std::istringstream ss(message.toStdString());
                    std::string token;
                    while (std::getline(ss, token, delimiter)) {
                        ui->messagesListWidget->addItem(QString::fromStdString(token));
                    }
                }
            }
        } else if (operationType == "delete message from personal correspondence")
        {
            if (ui->chatTitle->text() == jsonResponse["chat name"].toString() + "(private chat)"
                && userLogin_ == jsonResponse["user who sent"].toString())
            {
                ui->messagesListWidget->clear();
                if (message != "")
                {
                    char delimiter = '\n';
                    std::istringstream ss(message.toStdString());
                    std::string token;
                    while (std::getline(ss, token, delimiter)) {
                        ui->messagesListWidget->addItem(QString::fromStdString(token));
                    }
                }
            }
        } else if (operationType == "get all chats response" && userLogin_ == jsonResponse["user"].toString())
        {
            qDebug() << "get all chats response";
            if (message != "")
            {
                char delimiter = '\n';
                std::istringstream ss(message.toStdString());
                std::string token;
                while (std::getline(ss, token, delimiter)) {
                    ui->chatsListWidget->addItem(QString::fromStdString(token));
                }
            }
        } else if (operationType == "add new chat")
        {
            ui->chatsListWidget->addItem(message + "(" + jsonResponse["chat type"].toString() + ")");
        } else if (operationType == "ping")
        {
            sendPingResponse();
        }
    }
}

void chat::showInformationBox(QString message)
{
    QMessageBox messageBox;
    messageBox.setText(message);
    messageBox.show();

    QTimer::singleShot(500, &messageBox, &QMessageBox::close);
}

void chat::connectToDevice()
{
    auto ip = "127.0.0.1";
    auto port = 8001;
    QUrl url;
    url.setScheme("ws");
    url.setHost(ip);
    url.setPort(port);
    _controller.connectToDevice(url);
}

void chat::getAllChats()
{
    QJsonObject json;

    qDebug() << "getAllChats";

    json["operation type"] = "get all chats";
    json["user login"] = userLogin_;

    sendMessage(json);
}

void chat::on_openButton_clicked()
{
    QString chatName = ui->chatsListWidget->currentItem()->text();
    auto chatNameAndType = getChatNameAndType(chatName);

    QJsonObject json;

    qDebug() << chatNameAndType.second;
    qDebug() << chatNameAndType.first;

    if (chatNameAndType.second == "private chat")
    {
        json["operation type"] = "open private chat";
        json["user"] = chatNameAndType.first;
    } else
    {
        json["operation type"] = "open group chat";
        json["group"] = chatNameAndType.first;
    }

    json["user login"] = userLogin_;

    sendMessage(json);
}

void chat::device_dataReady(QByteArray data)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonResponse.object();

    handleResponse(jsonObject);
}

void chat::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    auto er = metaEnum.valueToKey(error);
    (new QErrorMessage(this))->showMessage(er);
}


void chat::on_joinGroupButton_clicked()
{
    QString chatName = ui->chatsListWidget->currentItem()->text();
    auto chatNameAndType = getChatNameAndType(chatName);

    QJsonObject json;

    QString operationType;

    if (chatNameAndType.second == "group")
    {
        operationType = "join group";
    } else
    {
        (new QErrorMessage(this))->showMessage("Can not join private chat! Only group!");
        return;
    }

    json["operation type"] = operationType;
    json["group"] = chatNameAndType.first;
    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_deleteChatButton_clicked()
{
    QString chatName = ui->chatsListWidget->currentItem()->text();
    auto chatNameAndType = getChatNameAndType(chatName);

    QJsonObject json;

    QString operationType;

    if (chatNameAndType.second == "private chat")
    {
        operationType = "end private chat";
    } else
    {
        (new QErrorMessage(this))->showMessage("Can not delete group! Only private chat!");
        return;
    }

    json["operation type"] = operationType;
    json["user"] = chatNameAndType.first;
    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_leaveGroupButton_clicked()
{
    QString chatName = ui->chatsListWidget->currentItem()->text();
    auto chatNameAndType = getChatNameAndType(chatName);

    QJsonObject json;

    QString operationType;

    if (chatNameAndType.second == "group")
    {
        operationType = "leave group";
    } else
    {
        (new QErrorMessage(this))->showMessage("Can not leave private chat! Only group!");
        return;
    }

    json["operation type"] = operationType;
    json["group"] = chatNameAndType.first;
    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_createGroupButton_clicked()
{
    qDebug() << "Create group";
    QString groupName = ui->groupNameLineEdit->text();

    QJsonObject json;
    json["operation type"] = "create group";
    json["name"] = groupName;
    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_startChatButton_clicked()
{
    QString userName = ui->chatsListWidget->currentItem()->text();

    auto chatNameAndType = getChatNameAndType(userName);

    QJsonObject json;
    json["operation type"] = "start chat";
    json["user"] = chatNameAndType.first;
    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_sendMessageButton_clicked()
{
    QString message = ui->messageLineEdit->text();

    QString chatName = ui->chatTitle->text();
    auto chatNameAndType = getChatNameAndType(chatName);

    if (chatNameAndType.first == "None")
    {
        showInformationBox("Choose chat first and open it!");
        return;
    }

    QJsonObject json;
    json["message"] = message;

    if (chatNameAndType.second == "group")
    {
        json["operation type"] = "send message to group";
        json["group"] = chatNameAndType.first;
    } else
    {
        json["operation type"] = "send message to pc";
        json["user"] = chatNameAndType.first;;
    }

    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_deleteMessageButton_clicked()
{
    QString message = ui->messagesListWidget->currentItem()->text();
    QString chatTitle = ui->chatTitle->text();
    auto chatNameAndType = getChatNameAndType(chatTitle);

    QJsonObject json;

    if (chatNameAndType.second == "group")
    {
        json["operation type"] = "delete message from group";
        json["group"] = chatNameAndType.first;
        json["message"] = message;
    }
    else
    {
        json["operation type"] = "delete message from personal correspondence";
        json["user"] = chatNameAndType.first;
        json["message"] = message;
    }

    json["user login"] = userLogin_;

    sendMessage(json);
}


void chat::on_connectButton_clicked()
{
    getAllChats();
    setButtonsState(true);
    ui->connectButton->setEnabled(false);
}

void chat::setGroupNameText(QString groupNameText)
{
    ui->groupNameLineEdit->setText(groupNameText);
}

void chat::setMessageText(QString message)
{
    ui->messageLineEdit->setText(message);
}


QString chat::getGroupNameText()
{
    return ui->groupNameLineEdit->text();
}


QString chat::getMessageText()
{
    return ui->messageLineEdit->text();
}

void chat::addMessageToMessageList(QString &message)
{
    ui->messagesListWidget->addItem(message);
}

void chat::addChatToChatList(QString &chat)
{
    ui->chatsListWidget->addItem(chat);
}

std::vector<QString> chat::getMessagesFromMessageList()
{
    int size = ui->messagesListWidget->count();
    std::vector<QString> messages;
    for (int i = 0; i < size; i++)
    {
        messages.push_back(ui->messagesListWidget->item(i)->text());
    }
    return messages;
}

std::vector<QString> chat::getChatsFromChatsList()
{
    int size = ui->chatsListWidget->count();
    std::vector<QString> chats;
    for (int i = 0; i < size; i++)
    {
        chats.push_back(ui->chatsListWidget->item(i)->text());
    }
    return chats;
}

