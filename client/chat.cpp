#include "chat.h"
#include "ui_chat.h"
#include <QMetaEnum>

chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    setDeviceContoller();
}

chat::~chat()
{
    delete ui;
}

void chat::on_lnIPAddress_textChanged(const QString &arg1)
{
    QString state = "0";
    if (arg1 == "...") {
        state = "";
    } else {
        QHostAddress address(arg1);
        if (QAbstractSocket::IPv4Protocol == address.protocol()) {
            state = "1";
        }
    }
    ui->lnIPAddress->setProperty("state", state);
    style()->polish(ui->lnIPAddress);
}


void chat::on_btnConnect_clicked()
{
    if (_controller.isConnected()) {
        _controller.disconnect();
    } else {
        auto ip = ui->lnIPAddress->text();
        auto port = ui->spnPort->value();
        QUrl url;
        url.setScheme("ws");
        url.setHost(ip);
        url.setPort(port);
        _controller.connectToDevice(url);
    }
}

void chat::device_connected()
{
    ui->lstConsole->addItem("Connected To Device");
    ui->btnConnect->setText("Disconnect");
    ui->grpSendData->setEnabled(true);
}

void chat::device_disconnected()
{
    ui->lstConsole->addItem("Disconnected from Device");
    ui->btnConnect->setText("Connect");
    ui->grpSendData->setEnabled(false);

}

void chat::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    ui->lstConsole->addItem(metaEnum.valueToKey(state));
}

void chat::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError >();
    ui->lstConsole->addItem(metaEnum.valueToKey(error));

}

void chat::device_dataReady(QByteArray data)
{
   ui->lstConsole->addItem(QString(data));
}

void chat::setDeviceContoller()
{
    connect(&_controller, &DeviceController::connected, this, &chat::device_connected);
    connect(&_controller, &DeviceController::disconnected, this, &chat::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &chat::device_stateChanged);
    connect(&_controller, &DeviceController::errorOccurred, this, &chat::device_errorOccurred);
    connect(&_controller, &DeviceController::dataReady, this, &chat::device_dataReady);
}


void chat::on_btnSend_clicked()
{
    QJsonObject json;
    json["operation type"] = "send message";
    json["message"] = ui->lnMessage->text().trimmed();

    QJsonDocument jsonDoc(json);
    QString message = jsonDoc.toJson();

    _controller.send(message);
}

void chat::setIpText(QString message)
{
    ui->lnIPAddress->setText(message);
}

void chat::setMessageText(QString message)
{
    ui->lnMessage->setText(message);
}


QString chat::getIpText()
{
    return ui->lnIPAddress->text();
}


QString chat::getMessageText()
{
    return ui->lnMessage->text();
}
