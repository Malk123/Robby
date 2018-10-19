#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QKeyEvent>

class control : public QObject
{

    Q_OBJECT

public:
    control();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void keyPress(QString value);
};

#endif // CONTROL_H
