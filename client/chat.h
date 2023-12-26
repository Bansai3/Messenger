#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QHostAddress>
#include "DeviceController.h"
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();

    void setIpText(QString message);

    void setMessageText(QString message);

    QString getIpText();

    QString getMessageText();

private slots:
    void on_lnIPAddress_textChanged(const QString &arg1);

    void on_btnConnect_clicked();

    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_errorOccurred(QAbstractSocket::SocketError);
    void device_dataReady(QByteArray data);


    void on_btnSend_clicked();

private:
    Ui::chat* ui;
    DeviceController _controller;

    void setDeviceContoller();
};

#endif
