#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include "chat.h"
#include <QMetaEnum>

class MainWindow;

namespace Ui {
class sign_in;
}

class sign_in : public QDialog
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = nullptr);
    ~sign_in();

    void setMainWindow(MainWindow* mw);


    void setLoginText(QString message);

    void setPasswordText(QString message);

    QString getLoginText();

    QString getPasswordText();

private slots:

    void device_dataReady(QByteArray data);

    void device_disconnected();

//    void device_stateChanged(QAbstractSocket::SocketState);

    void device_errorOccurred(QAbstractSocket::SocketError);

    void on_signIn_clicked();

    void on_back_clicked();

private:
    Ui::sign_in *ui;
    MainWindow* mw;
    chat* cw;
    DeviceController _controller;

    void setDeviceContoller();

    void handleResponse(QJsonObject& response);

    void sendMessage();

    void connectDevice();
};

#endif // SIGN_IN_H
