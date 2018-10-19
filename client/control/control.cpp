#include "control.h"

control::control()
{

}

bool control::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress){

        QKeyEvent* key = static_cast<QKeyEvent*>(event);

        switch(key->key()){
            case Qt::Key_W:
                emit keyPress("up");
                break;
            case Qt::Key_D:
                emit keyPress("right");
                break;
            case Qt::Key_A:
                emit keyPress("left");
                break;
            case Qt::Key_S:
                emit keyPress("down");
                break;
        }

        return true;
    }else{
        return QObject::eventFilter(obj, event);
    }

    return false;
}
