#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "src/receiveport.h"
#include <QMainWindow>

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
    void WriteTxt(const QByteArray &data) ;
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    ReceivePort *recPort ;
    int noofsamples ;
    int noofcurves ;
};

#endif // MAINWINDOW_H
