#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QErrorMessage>
#include "chat.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

class MainWindow;

namespace Ui {
class sign_up;
}

class sign_up : public QDialog
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

    void setMainWindow(MainWindow* mw);

    void setLoginText(QString message);

    void setPasswordText(QString message);

    void setNameText(QString message);

    void setSurnameText(QString message);

    QString getLoginText();

    QString getPasswordText();

    QString getNameText();

    QString getSurnameText();

private slots:
    void on_signUp_clicked();

    void on_back_clicked();

    void device_dataReady(QByteArray data);

    void device_disconnected();

    void device_stateChanged(QAbstractSocket::SocketState);

    void device_errorOccurred(QAbstractSocket::SocketError);

private:
    Ui::sign_up *ui;
    MainWindow* mw;
    DeviceController _controller;

    void setDeviceContoller();

    void handleResponse(QJsonObject& response);

    void sendMessage();

    void connectDevice();
};

#endif // SIGN_UP_H
