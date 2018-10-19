#ifndef GSTREAM_H
#define GSTREAM_H

#include <QObject>
#include "video/videooverlay.h"
#include <QApplication>

class Gstream : public QObject
{
    Q_OBJECT
public:
    explicit Gstream(QObject *parent = nullptr);
    WId xwinid;

private:
    GstElement *pipeline, *sink;

signals:

public slots:
    void startGstreamer();
    void stopGstreamer();

};

#endif // GSTREAM_H
