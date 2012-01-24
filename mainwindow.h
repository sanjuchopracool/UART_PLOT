#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "src/receiveport.h"
#include <QMainWindow>
#include<qwt/qwt_plot.h>
#include<qwt/qwt_plot_curve.h>
#include<QTimer>
#include<QQueue>
#include"YData.h"
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
    void updatedata(QString str);
    void on_pushButton_5_clicked();
    void replot();
private:
    Ui::MainWindow *ui;
    ReceivePort *recPort ;
    int noofsamples ;
    int noofcurves ;
    QwtPlotCurve *mycurves ;
    double *xdata;
    QTimer mytimer;
    QQueue<char> recData;
    QByteArray dataarray;
    QextSerialPort *port ;
    char ch,ch1;
    double y_data[10];
    YData *mycurvedata;
signals:
    void datalinerec_signal(QString);
};

#endif // MAINWINDOW_H
