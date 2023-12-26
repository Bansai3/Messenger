#include "sign_up.h"
#include "ui_sign_up.h"
#include "mainwindow.h"

sign_up::sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
    setDeviceContoller();
    connectDevice();
}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::setMainWindow(MainWindow *mw)
{
    this->mw = mw;
}

void sign_up::device_dataReady(QByteArray data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    handleResponse(jsonObj);
}

void sign_up::handleResponse(QJsonObject& response)
{
    auto responseType = response["operation type"];
    auto responseStatus = response["status"];


    if(responseStatus == "OK")
    {
        close();
        mw->show();
    } else
    {
        auto message = response["message"].toString();
        (new QErrorMessage(this))->showMessage(message);
    }
}

void sign_up::connectDevice()
{
    auto ip = "127.0.0.1";
    auto port = 8001;
    QUrl url;
    url.setScheme("ws");
    url.setHost(ip);
    url.setPort(port);
    _controller.connectToDevice(url);
}

void sign_up::on_signUp_clicked()
{
    if (_controller.isConnected())
    {
        sendMessage();
    }
}

void sign_up::sendMessage()
{
    QString name = ui->nameText->text();
    QString surname = ui->surnameText->text();
    QString login = ui->loginText->text();
    QString password = ui->passwordText->text();

    QJsonObject json;
    json["operation type"] = "sign up";
    json["name"] = name;
    json["surname"] = surname;
    json["login"] = login;
    json["password"] = password;

    QJsonDocument jsonDoc(json);
    QString message = jsonDoc.toJson();

    qDebug() << message;

    _controller.send(message);
}


void sign_up::on_back_clicked()
{
    close();
    mw->show();
}

void sign_up::setDeviceContoller()
{
//    connect(&_controller, &DeviceController::connected, this, &sign_up::sendMessage);
    connect(&_controller, &DeviceController::dataReady, this, &sign_up::device_dataReady);
    connect(&_controller, &DeviceController::disconnected, this, &sign_up::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &sign_up::device_stateChanged);
    connect(&_controller, &DeviceController::errorOccurred, this, &sign_up::device_errorOccurred);
}

void sign_up::device_disconnected()
{
    QMessageBox::information(this, "Connection error", "Disconnected from server");
}

void sign_up::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    QString message = QString::fromStdString("Device state changed - " + std::string(metaEnum.valueToKey(state)));
    QMessageBox::information(this, "State changed", message);
}

void sign_up::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError >();
    QString message = QString::fromStdString("ERROR: " + std::string(metaEnum.valueToKey(error)));
    QMessageBox::information(this, "Device error", message);
}

void sign_up::setLoginText(QString message)
{
    ui->loginText->setText(message);
}

void sign_up::setPasswordText(QString message)
{
    ui->passwordText->setText(message);
}

void sign_up::setNameText(QString message)
{
    ui->nameText->setText(message);
}

void sign_up::setSurnameText(QString message)
{
    ui->surnameText->setText(message);
}

QString sign_up::getLoginText()
{
    return ui->loginText->text();
}

QString sign_up::getPasswordText()
{
    return ui->passwordText->text();
}

QString sign_up::getNameText()
{
    return ui->nameText->text();
}

QString sign_up::getSurnameText()
{
    return ui->surnameText->text();
}
