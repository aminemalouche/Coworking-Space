#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QSystemTryIcon;
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
 MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    Ui::MainWindow *ui;
Arduino A;
    Client C ;
};

#endif // MAINWINDOW_H
