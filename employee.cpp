#include "employee.h"
#include "ui_employee.h"
#include<QThread>
//#include "mainwindow5.h"
#include "employe.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include "qcustomplot.h"
#include "widget5.h"

using namespace DuarteCorporation;

employee::employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
    ui->le_cin->setValidator (new QIntValidator(10000000,99999999,this));
    ui->le_nom->setValidator (new QRegExpValidator(QRegExp("[A-z]*")));
    ui->le_prenom->setValidator (new QRegExpValidator(QRegExp("[A-z]*")));
    ui->le_email->setValidator (new QRegExpValidator(QRegExp("[A-z]{1,20}@[a-z]{1,5}\\.[a-z]{1,4}")));
    ui->tab_emp->setModel(E.afficher());

    A.connect_arduino();
}

employee::~employee()
{
    delete ui;
}



void employee::on_pb_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString email=ui->le_email->text();
    QString dateN=ui->dateEdit->text();
    QString sexe=ui->comboBox_3->currentText();
    QString mdp=ui->le_mdp->text();
    QString rfid=ui->RFID->text();
Employe E(cin,nom,prenom,email,dateN,sexe,mdp,rfid);
bool test=E.ajouter();

QMessageBox msgBox;
if (test)
{
    msgBox.setText("Ajout avec succes.");
    ui->tab_emp->setModel(E.afficher());

}
else
    msgBox.setText("Echec d'ajout");
msgBox.exec();

}



void employee::on_pb_supprimer_clicked()
{
Employe E1;
E1.setcin(ui->le_cin->text().toInt());
bool test=E1.supprimer(E1.getcin());
QMessageBox msgBox;
if (test){
    msgBox.setText("Suppression avec succes.");
    ui->tab_emp->setModel(E.afficher());

}
else
    msgBox.setText("Echec de la suppression");
msgBox.exec();
}



void employee::on_modif_employe_clicked()
{
    QString nom=ui->le_nom->text();
        QString prenom=ui->le_prenom->text();
        int cin=ui->le_cin->text().toInt();
        QString email=ui->le_email->text();
        QString dateN=ui->dateEdit->text();
      QString sexe=ui->comboBox_3->currentText();
      QString mdp=ui->le_mdp->text();
           Employe E(cin,nom,prenom,email,dateN,sexe,mdp);
          bool test=E.modifier();
          if (test)
          { ui->tab_emp->setModel(E.afficher());
              QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);

      }
       else
          {QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);}

}




void employee::on_pb_recherche_clicked()
{
    QString rech= ui->le_rech->text();
       ui->tab_emp->setModel(E.recherche(rech));
}


void employee::on_pb_pdf_clicked()
{

    QString strStream;
        QTextStream out(&strStream);
       const int rowCount = ui->tab_emp->model()->rowCount();
       const int columnCount =ui->tab_emp->model()->columnCount();


       out <<  "<html>\n"
           "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
          <<  QString("<title>%1</title>\n").arg("employe")
          <<  "</head>\n"
             "<body bgcolor=grey link=#5000A0>\n"
                  "<h1>Liste des Employe</h1>"

             "<table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                            out << "<thead><tr bgcolor=#f0f0f0>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->tab_emp->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->tab_emp->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";
                            // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->tab_emp->isColumnHidden(column)) {
                                           QString data = ui->tab_emp->model()->data(ui->tab_emp->model()->index(row, column)).toString().simplified();
                                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                       }
                                   }
                                   out << "</tr>\n";
                               }
                               out <<  "</table>\n"
                                   "</body>\n"
                                   "</html>\n";
                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);
                //QTextDocument document;
                //document.setHtml(html);
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("employe.pdf");
                document->print(&printer);

}



void employee::on_pb_tri_nom_clicked()
{
    ui->tab_emp->setModel(E.trier());
}

void employee::on_pb_tri_prenom_clicked()
{
   ui->tab_emp->setModel(E.trierprenom());
}



void employee::makePlot_Type()
{
    QVector<double> x3(2), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customPlot2->xAxis, ui->customPlot2->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, employee::Statistique_Type());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customPlot2->replot();


    // move bars above graphs and grid below bars:
    ui->customPlot2->addLayer("abovemain", ui->customPlot2->layer("main"), QCustomPlot::limAbove);
    ui->customPlot2->addLayer("belowmain", ui->customPlot2->layer("main"), QCustomPlot::limBelow);
    ui->customPlot2->xAxis->grid()->setLayer("belowmain");
    ui->customPlot2->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
        Ticks<<1<<2;
    QVector<QString> labels;
    labels<<"HOMME"<<"FEMME";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customPlot2->xAxis->setTicker(textTicker);
    ui->customPlot2->xAxis->setSubTicks(false);
    ui->customPlot2->xAxis->setTickLength(0,4);
    ui->customPlot2->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot2->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot2->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot2->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot2->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot2->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot2->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot2->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot2->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot2->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot2->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot2->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot2->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot2->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(10, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customPlot2->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customPlot2->axisRect()->setBackground(axisRectGradient);

    ui->customPlot2->rescaleAxes();
    ui->customPlot2->xAxis->setRange(0, 7);
    ui->customPlot2->yAxis->setRange(0, 10);
}
QVector<double> employee::Statistique_Type()
{
    QSqlQuery q;
    QVector<double> stat(2);
    stat[0]=0;
    stat[1]=0;

    q.prepare("SELECT SEXE FROM EMPLOYE where SEXE='HOMME'");
    q.exec();
    while (q.next())
    {
            stat[0]++;
    }
    q.prepare("SELECT SEXE FROM EMPLOYE where SEXE='FEMME'");
    q.exec();
    while (q.next())
    {
            stat[1]++;
    }

    return stat;
}

void employee::on_pushButton_statis_clicked()
{
    employee::makePlot_Type();

}

void employee::on_pushButton_clicked()
{

    widget5 w;
    w.exec();
}

void employee::on_tri_eamil_clicked()
{
  ui->tab_emp->setModel(E.trieemail());
}

void employee::on_pushButton_2_clicked()
{

QString x=A.read_from_arduino();
qInfo()<<"nom= "<<x<<endl;
x=x.simplified();
x.replace(" ","");
ui->RFID->setText(x);

}
