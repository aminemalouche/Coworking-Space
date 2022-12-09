#include "widget5.h"
#include "ui_widget5.h"
#include "DuMesengerConnectionDialog.h"
#include <QTcpSocket>
#include <QTextStream>

namespace DuarteCorporation
{
widget5::widget5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::widget5)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->textEdit->append(text);
    });
}

widget5::~widget5()
{
    delete ui;
}
void widget5::on_send_clicked()
{
    QTextStream T(mSocket);
    T << ui->nickname_2->text() <<" : " << ui->message_2->text();
    mSocket->flush();
    ui->message_2->clear();
}

void widget5::on_bind_clicked()
{
   DuMesengerConnectionDialog D (this);
   if(D.exec() == QDialog ::Rejected){
       return;
   }
   mSocket->connectToHost(D.hostname(),D.port());


}
}

