#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>
class Client
{
public:
    Client();
    Client (int,QString,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getdate();
    QString getsexe();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setdate(QString);
    void setsexe(QString);
    bool ajouter();
    bool modifier(QString);

  QSqlQueryModel* afficher();
  bool supprimer(int);
private :
 int id ;
 QString nom ,prenom,date,sexe ;
};
#endif // CLIENT_H
