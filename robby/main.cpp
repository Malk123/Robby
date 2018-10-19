#include <QApplication>
#include <QDebug>
#include <Sockets/command.h>
#include <Sockets/video.h>
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Robby v0.1 started";

    gst_init (&argc,&argv);

    QThread *control_socket_thread = new QThread();
    command *s = new command();
    s->moveToThread(control_socket_thread);
    control_socket_thread->start();

    QObject::connect(control_socket_thread, SIGNAL (started()), s, SLOT (doConnect()));

    return a.exec();
}
