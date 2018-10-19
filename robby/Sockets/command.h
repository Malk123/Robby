#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QtCore>

#include <wiringPi.h>
#include <softPwm.h>
#include <Sockets/video.h>

class command : public QObject
{

    Q_OBJECT

public:
    explicit command(QObject *parent = 0);
    QTcpSocket *socket;
    void forward();
    void stop();
    void left();
    void right();

signals:

public slots:
    void newConnection();
    void doConnect();
    void readyRead();
    void clientDisconnected();

private:
    QTcpServer *server;
    QThread *video_socket_thread;
    video *v;
};

#endif // COMMAND_H
