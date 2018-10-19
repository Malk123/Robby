#ifndef CONTROLSOCKET_H
#define CONTROLSOCKET_H

#include <QObject>
#include <QtCore>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QAbstractSocket>

class ControlSocket : public QObject
{

    Q_OBJECT

public:
    ControlSocket();

private:
    QTcpSocket *socket;
    bool terminate = false;

public slots:
    void doConnect(QString ip);
    void write(QString text);
    void doDisconnect();
    bool isConnected();

signals:
    void connected();
    void disconnected();

};

#endif // CONTROLSOCKET_H
