#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Employe::Employe()
{
cin=0; nom="";prenom="";email=""; dateN="";sexe="";mdp="";
}


Employe::Employe(int cin,QString nom,QString prenom,QString email,QString dateN,QString sexe,QString mdp){
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->dateN=dateN;
    this->sexe=sexe;
    this->mdp=mdp;

}

Employe::Employe(int cin,QString nom,QString prenom,QString email,QString dateN,QString sexe,QString mdp,QString rfid){
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->dateN=dateN;
    this->sexe=sexe;
    this->mdp=mdp;
    this->rfid=rfid;
}


int Employe::getcin(){
    return cin;
}
QString Employe::getnom(){
    return nom;
}
QString Employe::getprenom(){
    return prenom;
}
QString Employe::getemail(){
    return email;
}
QString Employe::getsexe(){
    return sexe;
}
QString Employe::getdateN(){
    return dateN;}
QString Employe::getmdp(){
    return mdp;}


void Employe::setcin(int cin){this->cin=cin;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
void Employe::setemail(QString email){this->email=email;}
void Employe::setdate(QString dateN){this->dateN=dateN;}
void Employe::setsexe(QString sexe){this->sexe=sexe;}
void Employe::setmdp(QString mdp){this->mdp=mdp;}




bool Employe::ajouter(){
QSqlQuery query;
QString cin_string= QString::number(cin);
query.prepare("INSERT INTO EMPLOYE (CIN,NOM,PRENOM,EMAIL,DATEE,SEXE,MDP,RFID)""VALUES (:cin, :nom, :prenom, :email, :dateN, :sexe, :mdp,:rfid)");
query.bindValue(":cin",cin_string);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":email",email);
query.bindValue(":sexe",sexe);
query.bindValue(":dateN",dateN);
query.bindValue(":mdp",mdp);
query.bindValue(":rfid",rfid);
return query.exec();
}



QSqlQueryModel* Employe::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM EMPLOYE");
model->setHeaderData(0,Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
model->setHeaderData(5,Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(6,Qt::Horizontal, QObject::tr("MDP"));
  return model;
}



bool Employe::supprimer(int cin)
{
    QSqlQuery query;

    query.prepare("DELETE FROM EMPLOYE where cin=:cin");
    query.bindValue(0,cin);
    return query.exec();
}



bool Employe::modifier()
 {
    QSqlQuery query;

        QString cin_string= QString::number(cin);
        query.prepare("UPDATE EMPLOYE set  cin=:cin, nom=:nom, prenom=:prenom , email=:email , DATEE=:dateN ,sexe=:sexe,MDP=:mdp WHERE cin=:cin ");
        query.bindValue(":cin",cin);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":email",email);
        query.bindValue(":dateN",dateN);
        query.bindValue(":sexe",sexe);
        query.bindValue(":mdp",mdp);
        return query.exec();

 }


QSqlQueryModel * Employe::recherche(QString rech)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where cin like '%"+rech+"%' or nom like '%"+rech+"%' or prenom like '%"+rech+"%' ;");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("DATEE"));
    return model;
}

QSqlQueryModel * Employe::trier(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE ORDER BY NOM");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("DATEE"));
    return model;
}


QSqlQueryModel * Employe::trierprenom(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE ORDER BY PRENOM");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("DATEE"));
    return model;
}

QSqlQueryModel * Employe::trieemail(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from EMPLOYE ORDER BY email");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("DATEE"));
    return model;
}


