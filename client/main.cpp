#include <QApplication>
#include <QThread>
#include <QDebug>

#include <control/control.h>
#include <socket/controlsocket.h>
#include <socket/gstream.h>
#include <form/form.h>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{

    gst_init (&argc, &argv);

    QApplication app(argc, argv);

    /**
     * Shows the Form.
     * @brief widget
     */
    Form widget;
    widget.show();

    control *con = new control();
    ControlSocket *cs = new ControlSocket();
    QThread *thread = new QThread();
    Gstream *v = new Gstream();

    /**
      * Install the Evenfilter for Key inserts to control the engines.
      */
    widget.installEventFilter(con);
    widget.cs = cs;

    /**
      * Copy the ID of the Child Widget to GStreamer Class.
      */
    v->xwinid = widget.child_widget;

    v->moveToThread(thread);
    thread->start();

    QObject::connect(con, SIGNAL (keyPress(QString)), cs, SLOT (write(QString)));
    QObject::connect(cs, SIGNAL (connected()), v, SLOT (startGstreamer()));
    QObject::connect(cs, SIGNAL (disconnected()), v, SLOT (stopGstreamer()));

    return app.exec();
}
