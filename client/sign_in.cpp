#include "sign_in.h"
#include "ui_sign_in.h"
#include "mainwindow.h"

sign_in::sign_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    setDeviceContoller();
    connectDevice();
}

sign_in::~sign_in()
{
    delete ui;
}

void sign_in::connectDevice()
{
    auto ip = "127.0.0.1";
    auto port = 8001;
    QUrl url;
    url.setScheme("ws");
    url.setHost(ip);
    url.setPort(port);
    _controller.connectToDevice(url);
}

void sign_in::on_signIn_clicked()
{
    if (_controller.isConnected())
    {
        sendMessage();
    }
}

void sign_in::sendMessage()
{
    QString login = ui->logIn->text();
    QString password = ui->password->text();

    QJsonObject json;
    json["operation type"] = "sign in";
    json["login"] = login;
    json["password"] = password;

    QJsonDocument jsonDoc(json);
    QString message = jsonDoc.toJson();

    _controller.send(message);
}


void sign_in::on_back_clicked()
{
    close();
    mw->show();
}

void sign_in::setMainWindow(MainWindow *mw)
{
    this->mw = mw;
}

void sign_in::device_dataReady(QByteArray data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    handleResponse(jsonObj);
}

void sign_in::handleResponse(QJsonObject& response)
{
    auto responseType = response["operation type"];
    auto responseStatus = response["status"];


    if(responseStatus == "OK")
    {
        close();
        cw = new chat();
        cw->show();
    } else
    {
        auto message = response["message"].toString();
        (new QErrorMessage(this))->showMessage(message);
    }
}


void sign_in::setDeviceContoller()
{
//    connect(&_controller, &DeviceController::connected, this, &sign_in::sendMessage);
    connect(&_controller, &DeviceController::dataReady, this, &sign_in::device_dataReady);
    connect(&_controller, &DeviceController::disconnected, this, &sign_in::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &sign_in::device_stateChanged);
    connect(&_controller, &DeviceController::errorOccurred, this, &sign_in::device_errorOccurred);
}

void sign_in::device_disconnected()
{
    QMessageBox::information(this, "Connection error", "Disconnected from server");
}

void sign_in::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    QString message = QString::fromStdString("Device state changed - " + std::string(metaEnum.valueToKey(state)));
    QMessageBox::information(this, "State changed", message);
}

void sign_in::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError >();
    QString message = QString::fromStdString("ERROR: " + std::string(metaEnum.valueToKey(error)));
    QMessageBox::information(this, "Device error", message);
}

void sign_in::setLoginText(QString message)
{
    ui->logIn->setText(message);
}

void sign_in::setPasswordText(QString message)
{
    ui->password->setText(message);
}

QString sign_in::getLoginText()
{
    return ui->logIn->text();
}

QString sign_in::getPasswordText()
{
    return ui->password->text();
}
