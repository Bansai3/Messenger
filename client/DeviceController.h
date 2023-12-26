#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    void connectToDevice(QUrl url);
    void disconnect();
    QAbstractSocket::SocketState state();
    bool isConnected();
    void send(QString message);

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReady(QByteArray);

private slots:
    void socket_stateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead(QString message);
private:
    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // DEVICECONTROLLER_H
