#ifndef MAINAMINE_H
#define MAINAMINE_H

#include <QDialog>
#include <QMainWindow>
#include "employe.h"
#include <QSqlQuery>
#include "connection.h"


namespace Ui {
class MainAmine;
}

class MainAmine : public QDialog
{
    Q_OBJECT

public:
    explicit MainAmine(QWidget *parent = nullptr);
    ~MainAmine();

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::MainAmine *ui;
        QSqlDatabase db;
};

#endif // MAINAMINE_H
