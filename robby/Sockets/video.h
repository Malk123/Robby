#ifndef VIDEO_H
#define VIDEO_H

#include <gst/gst.h>
#include <QDebug>
#include <QObject>
#include <QHostAddress>

class video : public QObject
{

    Q_OBJECT

public:
    video();
    QHostAddress ip;

private:
    int* argc;
    char **argv[];
    GMainLoop *loop;
    GstElement *pipeline, *videosrc, *conv,*enc, *pay, *udp, *filter, *videoparse;
    GstCaps *cap;

public slots:
    void videoStart();
    void videoStop();

};

#endif // VIDEO_H
