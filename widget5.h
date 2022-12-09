#ifndef WIDGET5_H
#define WIDGET5_H

#include <QDialog>

namespace Ui {
class widget5;
}
class QTcpSocket;
namespace DuarteCorporation
{
class widget5 : public QDialog
{
    Q_OBJECT

public:
    explicit widget5(QWidget *parent = nullptr);
    ~widget5();

private slots:
    void on_send_clicked();
    void on_bind_clicked();
private:
    Ui::widget5 *ui;
    QTcpSocket *mSocket;

};
}
#endif // WIDGET5_H
