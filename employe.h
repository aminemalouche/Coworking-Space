#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

class Employe
{
public:
    Employe();
     Employe(int,QString,QString,QString,QString,QString,QString);
    Employe(int,QString,QString,QString,QString,QString,QString,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString getdateN();
    QString getsexe();
    QString getmdp();
   void setcin(int);
   void setnom(QString);
   void setprenom(QString);
   void setemail(QString);
   void setdate(QString);
   void setsexe(QString);
   void setmdp(QString);
   bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int);
   bool modifier();
QSqlQueryModel * recherche(QString rech);
QSqlQueryModel * trier();
QSqlQueryModel * trierprenom();
QSqlQueryModel * trieemail();
QChartView *stat_type();
private:
    int cin;
    QString nom,prenom,email;
QString dateN,sexe,mdp,rfid;

};

#endif // EMPLOYE_H
