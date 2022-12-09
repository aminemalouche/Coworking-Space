#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include "employe.h"
#include "arduino.h"

namespace Ui {
class employee;
}

class employee : public QDialog
{
    Q_OBJECT

public:
    explicit employee(QWidget *parent = nullptr);
    ~employee();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_modif_employe_clicked();

    void on_pb_recherche_clicked();

    void on_pb_pdf_clicked();

    void on_pb_tri_nom_clicked();

    void on_pb_tri_prenom_clicked();

    void on_pushButton_statis_clicked();
    void makePlot_Type();
    QVector<double> Statistique_Type();


    void on_pushButton_clicked();

    void on_tri_eamil_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::employee *ui;
    Employe E;
    Arduino A;

};

#endif // EMPLOYEE_H
