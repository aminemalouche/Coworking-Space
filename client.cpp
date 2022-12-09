 #include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
Client::Client()
{
id=0 ; nom=""; prenom="";  date=""; sexe="";
}


Client :: Client (int id ,QString nom, QString prenom,QString date,QString sexe)
{this->id=id ;this->nom=nom ;this->prenom=prenom ; this->date=date ;this->sexe=sexe ;}
int Client  :: getid(){return id;}
QString Client :: getnom(){return nom;}
QString Client :: getprenom(){return prenom;}
QString Client :: getdate(){return date;}
QString Client :: getsexe(){return sexe;}
void Client:: setid(int id){this->id=id;}
void Client:: setnom(QString nom){this->nom=nom;}
void Client:: setprenom(QString prenom){this->prenom=prenom;}
void Client:: setdate(QString date){this->date=date;}
void Client:: setsexe(QString sexe){this->sexe=sexe;}

bool Client::ajouter()
{


QString id_string=QString::number(id);
QSqlQuery query;
       query.prepare("INSERT INTO CLIENT(ID,NOM,PRENOM,DATEE,SEXE)" "VALUES (:ID, :NOM, :PRENOM, :DATEE , :SEXE);");
      query.bindValue(":ID", id_string);
      query.bindValue(":NOM", nom);
      query.bindValue(":PRENOM", prenom);
      query.bindValue(":DATEE", date);
      query.bindValue(":SEXE", sexe);
return query.exec() ;
}


bool Client::supprimer(int id)
{QSqlQuery query;


    query.prepare("Delete from client where id= :id ;");
    query.bindValue(":id", id);

return query.exec() ;
}
QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM CLIENT");
          model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject:: tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal, QObject:: tr("PRENOM"));
             model->setHeaderData(3, Qt::Horizontal, QObject:: tr("SEXE"));
              model->setHeaderData(4, Qt::Horizontal, QObject:: tr("DATE"));
    return model;
}

bool Client::modifier(QString RID){
 QSqlQuery query;
      query.prepare("UPDATE client SET id= :ID, nom= :NOM , prenom= :PRENOM WHERE id= :RID; ");
      query.bindValue(":RID", RID);
      query.bindValue(":ID", id);
      query.bindValue(":NOM",nom);
      query.bindValue(":PRENOM",prenom);

return query.exec();


}
