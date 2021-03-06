#include "controlsocket.h"

ControlSocket::ControlSocket()
{
    socket = new QTcpSocket (this);
}

void ControlSocket::write(QString text){
    if(this->isConnected()){
        QByteArray ba = text.toLatin1();
        const char *c_str2 = ba.data();
        socket->write(c_str2);
        socket->waitForBytesWritten(100);
    }
}

void ControlSocket::doDisconnect(){
    qDebug() << "Control Disconnected!";
    socket->disconnectFromHost();
    if(socket->state() == QAbstractSocket::UnconnectedState){
        qDebug() << "disconnected";
        emit disconnected();
    }

   // this->deleteLater();
}

bool ControlSocket::isConnected() {
    if(socket->state() == QAbstractSocket::ConnectedState  || socket->state() == QAbstractSocket::ConnectingState){
        return true;
    }else{
        return false;
    }
}

void ControlSocket::doConnect(QString ip) { // Process. Start processing data.


    socket->connectToHost(ip, 9999);

    if(socket->waitForConnected(5000))
    {

        emit connected();
        qDebug() << "Control Connected!";
    }
    else
    {
        qDebug() << "Control not connected!";
    }
}
