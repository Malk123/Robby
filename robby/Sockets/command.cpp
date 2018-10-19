#include "command.h"

int pin1 = 1;
int pin2 = 2;
int pin3 = 3;

int pin4 = 23;
int pin5 = 24;
int pin6 = 25;

command::command(QObject *parent) :
    QObject(parent)
{

    wiringPiSetup();

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
    pinMode(pin5, OUTPUT);
    pinMode(pin6, OUTPUT);

    softPwmCreate(pin1, 0, 100);
    softPwmCreate(pin2, 0, 100);
    softPwmCreate(pin3, 0, 100);

    softPwmCreate(pin4, 0, 100);
    softPwmCreate(pin5, 0, 100);
    softPwmCreate(pin6, 0, 100);



}

void command::forward(){
    softPwmWrite(pin1, 100);
    softPwmWrite(pin2, 0);
    softPwmWrite(pin3, 100);

    softPwmWrite(pin4, 100);
    softPwmWrite(pin5, 0);
    softPwmWrite(pin6, 100);
}

void command::left(){
    softPwmWrite(pin1, 100);
    softPwmWrite(pin2, 0);
    softPwmWrite(pin3, 100);

    softPwmWrite(pin4, 100);
    softPwmWrite(pin5, 100);
    softPwmWrite(pin6, 0);
}

void command::right(){
    softPwmWrite(pin1, 100);
    softPwmWrite(pin2, 100);
    softPwmWrite(pin3, 0);

    softPwmWrite(pin4, 100);
    softPwmWrite(pin5, 0);
    softPwmWrite(pin6, 100);
}

void command::stop(){
    softPwmWrite(pin1, 0);
    softPwmWrite(pin2, 0);
    softPwmWrite(pin3, 0);

    softPwmWrite(pin4, 0);
    softPwmWrite(pin5, 0);
    softPwmWrite(pin6, 0);
}

void command::readyRead(){


    QString arr = socket->readAll().data();

    qDebug() << arr;

    if(arr == "up"){
        this->forward();
    }
    if(arr == "down"){
        this->stop();
    }
    if(arr == "left"){
        this->left();
    }
    if(arr == "right"){
        this->right();
    }

}

void command::doConnect(){
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Control Socket could not start";
    }
    else
    {
        qDebug() << "Control Socket started!";
    }
}

void command::clientDisconnected(){
    video_socket_thread->quit();
    qDebug() << "Client disconnected.";
}

void command::newConnection(){

    // need to grab the socket
    socket = server->nextPendingConnection();

    qDebug() <<  "Client Connected";

    video_socket_thread = new QThread();
    v = new video();
    v->ip = socket->peerAddress();
    v->moveToThread(video_socket_thread);
    video_socket_thread->start();

    connect(video_socket_thread, SIGNAL (started()), v, SLOT (videoStart()), Qt::DirectConnection);
    connect(socket, SIGNAL (disconnected()), v, SLOT (videoStop()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()), Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);

    socket->waitForReadyRead(-1);
}
