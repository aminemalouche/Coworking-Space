#include "mainwindow7.h"
#include "ui_mainwindow7.h"
#include "client.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSettings>
#include <QSystemTrayIcon>
#include<QPainter>
#include<QPdfWriter>

mainwindow7::mainwindow7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow7)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0, 9999999, this));

 ui->tableView->setModel(C.afficher());
 QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                    QCoreApplication::organizationName(), QCoreApplication::applicationName());

 ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
 A.connect_arduino();
}

mainwindow7::~mainwindow7()
{
    delete ui;
}

void mainwindow7::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
     QString date=ui->Date->text();
      QString sexe=ui->Sexe->currentText();
  Client C;
  C.setid(id);
  C.setnom(nom);
  C.setprenom(prenom);
   C.setdate(date);
    C.setsexe(sexe);
  bool test=C.ajouter();

 if (test)
         { ui->tableView->setModel(C.afficher());

     QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("Ajout effectué.\n"
                                       "click cancel to exit."),QMessageBox::Cancel);
  }
  else
     QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                        QObject::tr("Ajout non effectué.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
 QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

                       notifyIcon->show();
                      notifyIcon->setIcon(QIcon(":/icon.png"));

                       notifyIcon->showMessage("GESTION DES  CLIENT ","ajouter notification ",QSystemTrayIcon::Information,15000);
//Liste client pret dans PDF
  //.exec();*/
}

void mainwindow7::on_pb_supprimer_clicked()
{
  Client C1;C1.setid(ui->le_id_supp->text().toInt());
  bool test=C1.supprimer(C1.getid());
  QMessageBox msgBox;
  if (test)
  { ui->tableView->setModel(C.afficher());
      QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("Suppression effectué.\n"
                                        "click cancel to exit."),QMessageBox::Cancel);}
  else
     QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                        QObject::tr("Suppression non effectué.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

                        notifyIcon->show();
                       notifyIcon->setIcon(QIcon(":/icon.png"));

                        notifyIcon->showMessage("GESTION DES  CLIENT ","supprimer notification",QSystemTrayIcon::Information,15000);

}

void mainwindow7::on_modifier_clicked()
{  Client C;
    C.setid(ui->new_id->text().toInt());
    C.setnom(ui->new_nom->text());
    C.setprenom(ui->new_prenom->text());

    bool test=C.modifier(ui->old_id->text());

   if (test)
           { ui->tableView->setModel(C.afficher());
       QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Modification effectué.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
    }
    else
       QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                          QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

                         notifyIcon->show();
                        notifyIcon->setIcon(QIcon(":/icon.png"));

                         notifyIcon->showMessage("GESTION DES  CLIENT ","modifier notification",QSystemTrayIcon::Information,15000);
}

void mainwindow7::on_pb_recherche_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from client where  ((ID ||  NOM || datee || SEXE || prenom  ) like '%"+ui->recherche_in->text()+"%');");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("NOM"));
      model->setHeaderData(2, Qt::Horizontal, QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal, QObject:: tr("SEXE"));
        model->setHeaderData(4, Qt::Horizontal, QObject:: tr("DATE"));
         ui->tableView->setModel(model);


}

void mainwindow7::on_recherche_in_cursorPositionChanged(int arg1, int arg2)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from client where  ((ID ||  NOM || datee  || prenom  ) like '%"+ui->recherche_in->text()+"%');");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("NOM"));
      model->setHeaderData(2, Qt::Horizontal, QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal, QObject:: tr("SEXE"));
        model->setHeaderData(4, Qt::Horizontal, QObject:: tr("DATE"));
         ui->tableView->setModel(model);
}

void mainwindow7::on_tri_id_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from client order by ID;");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("NOM"));
      model->setHeaderData(2, Qt::Horizontal, QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal, QObject:: tr("SEXE"));
        model->setHeaderData(4, Qt::Horizontal, QObject:: tr("DATE"));
         ui->tableView->setModel(model);
}

void mainwindow7::on_radioButton_2_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from client order by DATEE;");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("NOM"));
      model->setHeaderData(2, Qt::Horizontal, QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal, QObject:: tr("SEXE"));
        model->setHeaderData(4, Qt::Horizontal, QObject:: tr("DATE"));
         ui->tableView->setModel(model);
}


void mainwindow7::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/Eskander Dahmen/Desktop/Atelier_Connexion/Tableau.pdf");
                                 QPainter painter(&pdf);

                                int i = 5000;

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(1100,1200,"Liste Des Clients");
                                     painter.setPen(Qt::red);

                                     painter.drawRect(100,100,7300,2600);

                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.drawText(200,4300,"ID");
                                     painter.drawText(1300,4300,"DATE");
                                     painter.drawText(2100,4300,"SEXE");
                                     painter.drawText(3100,4300,"NOM");
                                     painter.drawText(4100,4300,"PRENOM");


                                     QSqlQuery query;
                                     query.prepare("select * from CLIENT");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(200,i,query.value(0).toString());
                                         painter.drawText(1300,i,query.value(1).toString());
                                         painter.drawText(2100,i,query.value(2).toString());
                                         painter.drawText(3100,i,query.value(3).toString());
                                         painter.drawText(4100,i,query.value(4).toString());





                                        i = i + 500;
                                     }


                          painter.end();
                          QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

                                                notifyIcon->show();
                                               notifyIcon->setIcon(QIcon(":/icon.png"));

                                                notifyIcon->showMessage("GESTION DES  CLIENT ","PDF prêt",QSystemTrayIcon::Information,15000);

}


void mainwindow7::on_pushButton_clicked()
{
QString temp;
temp=A.read_from_arduino();
ui->label_11->setText("Capteur Température: "+temp);
}


