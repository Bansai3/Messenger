#include "DeviceController.h"

DeviceController::DeviceController(QObject *parent):
    QObject{parent}
{
    connect(&m_webSocket, &QWebSocket::connected, this, &DeviceController::connected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &DeviceController::disconnected);
    connect(&m_webSocket, &QWebSocket::errorOccurred, this, &DeviceController::errorOccurred);
    connect(&m_webSocket, &QWebSocket::stateChanged, this, &DeviceController::socket_stateChanged);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &DeviceController::socket_readyRead);
}

void DeviceController::connectToDevice(QUrl newUrl)
{
    if (state() == QAbstractSocket::ConnectedState) {
        if (m_url.toString() == newUrl.toString()) {
            return;
        }
        m_webSocket.close();
    }
    m_url = newUrl;
    m_webSocket.open(QUrl(m_url));
}

void DeviceController::disconnect()
{
    m_webSocket.close();
}

QAbstractSocket::SocketState DeviceController::state()
{
    return m_webSocket.state();
}

bool DeviceController::isConnected()
{
    return m_webSocket.state() == QAbstractSocket::ConnectedState;
}

void DeviceController::send(QString message)
{
    m_webSocket.sendTextMessage(message);
}

void DeviceController::socket_stateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {
        m_webSocket.close();
    }
    emit stateChanged(state);
}

void DeviceController::socket_readyRead(QString message)
{
    emit dataReady(message.toUtf8());
}
