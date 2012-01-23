#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "src/receiveport.h"
#include <QMainWindow>
#include "CurveData.h"
#include<qwt/qwt_plot.h>
#include<qwt/qwt_plot_curve.h>
#include<QTimer>
#include<QQueue>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void received_signal(const QByteArray &data,int) ;
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void replot();
private:
    Ui::MainWindow *ui;
    ReceivePort *recPort ;
    int noofsamples ;
    int noofcurves ;
    CurveData *mycurvedatas ;
    QwtPlotCurve *mycurves ;
    double *xdata;
    QTimer mytimer;
    QQueue<char> recData;
    QByteArray dataarray;
    QString datastring;
    char ch;
};

#endif // MAINWINDOW_H
