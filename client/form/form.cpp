#include "form.h"

Form::Form(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    child_widget = ui.videoWidget->winId();
}


void Form::connectButtonAction()
{

    if(this->cs->isConnected() == true){
        this->cs->doDisconnect();
        ui.ipInput->setDisabled(false);
        ui.pushButton->setText("Connect");
    }else{
        this->cs->doConnect(ui.ipInput->text());
        ui.ipInput->setDisabled(true);
        ui.pushButton->setText("Disconnect");
    }

    qDebug() << ui.ipInput->text();
}
