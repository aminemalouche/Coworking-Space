#ifndef MAINWINDOW7_H
#define MAINWINDOW7_H

#include <QDialog>
#include "client.h"
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow7;
}
class QSystemTryIcon;
QT_END_NAMESPACE
class mainwindow7 : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow7(QWidget *parent = nullptr);
    ~mainwindow7();
private slots:


    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();



    void on_modifier_clicked();

    void on_pb_recherche_clicked();

    void on_recherche_in_cursorPositionChanged(int arg1, int arg2);

    void on_tri_id_clicked();

    void on_radioButton_2_clicked();



    void on_PDF_clicked();

    void on_pushButton_clicked();

private:
    Ui::mainwindow7 *ui;
Arduino A;
    Client C ;
};

#endif // MAINWINDOW7_H
