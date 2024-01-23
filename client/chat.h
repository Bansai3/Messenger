#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include "DeviceController.h"
#include <QHostAddress>
#include <QErrorMessage>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>
#include <sstream>
#include <QTimer>

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QString& userLogin, QWidget *parent = nullptr);
    ~chat();

    void setUserLogin(QString& userLogin);

    void ConnectChat();

    void getAllChats();

    void setGroupNameText(QString groupNameText);

    void setMessageText(QString message);

    QString getGroupNameText();

    QString getMessageText();

    void addMessageToMessageList(QString& message);

    void addChatToChatList(QString& chat);

    std::vector<QString> getMessagesFromMessageList();

    std::vector<QString> getChatsFromChatsList();


private slots:
    void on_openButton_clicked();

    void on_joinGroupButton_clicked();

    void on_deleteChatButton_clicked();

    void on_leaveGroupButton_clicked();

    void on_createGroupButton_clicked();

    void on_startChatButton_clicked();

    void on_sendMessageButton_clicked();

    void on_deleteMessageButton_clicked();

    void device_dataReady(QByteArray data);

    void device_errorOccurred(QAbstractSocket::SocketError error);

    void on_connectButton_clicked();

private:
    Ui::chat *ui;
    DeviceController _controller;
    QString userLogin_;

private:
    std::pair<QString, QString> getChatNameAndType(QString& chatTitle);

    void handleResponse(QJsonObject& jsonResponse);

    void showInformationBox(QString message);

    void connectToDevice();

    void setDeviceContoller();

    void sendMessage(QJsonObject& json);

    void setButtonsState(bool state);

    void setButtonsHoverState();

    void sendPingResponse();
};

#endif // CHAT_H
