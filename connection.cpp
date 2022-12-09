#include "connection.h"
#include <iostream>

using namespace std;
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A26");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("amine");//inserer mot de passe de cet utilisateur
//db.setPort(1521);

//cout<<db.QSqlDatabase::lastError()<<endl;




    return  db.open();
}

