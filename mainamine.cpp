#include "mainamine.h"
#include "ui_mainamine.h"
#include "employe.h"
#include "employee.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include "qcustomplot.h"
#include "arduino.h"


MainAmine::MainAmine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainAmine)
{
    ui->setupUi(this);
}

MainAmine::~MainAmine()
{
    delete ui;
}

void MainAmine::on_pushButton_4_clicked()
{
    Arduino A;
            Connection c;

            QSqlQuery query(db);
            QString select = "SELECT NOM from EMPLOYE where NOM=? and MDP=?";
            qDebug() << select;
            query.prepare(select);
            query.addBindValue(ui->lineEdit_8->text());
            query.addBindValue(ui->lineEdit_9->text());
            query.exec();

           if (query.exec())
            {

                int count=0;
                while (query.next())
                {
                    count++;
                }
                if (count==1)
                {
                    ui->label_4->setText(" username and password are correct ");
                    this->hide();
                    employee em ;
                    em.exec();
                }

                 else if (count<1)
                {
                    ui->label_4->setText(" username and password are incorrect ");

                    //c.closeconnection();

                }
            }
}
