#ifndef FORM_H
#define FORM_H

#include <QObject>
#include "ui_form.h"
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <socket/controlsocket.h>
#include <socket/gstream.h>

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    QPushButton *pushButton;
    ControlSocket *cs;
    int child_widget;

private:
    Ui::Form ui;

private slots:
    void connectButtonAction();
};

#endif // FORM_H
