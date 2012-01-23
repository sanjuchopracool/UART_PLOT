#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMetaType>
#include<qextserialport.h>
#include<QValidator>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<iostream>
using namespace std ;
Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    double xaxisdata[20000];
    for(int i=0 ; i<20000;i++)
        xaxisdata[i]=i;
    xdata =xaxisdata;
    mycurvedata =new YData[10];
    mycurves =new QwtPlotCurve[10];
    ui->setupUi(this);
    ui->comboBox->addItem(tr("/dev/ttyS0"),QVariant::fromValue(QString("/dev/ttyS0")));
    ui->comboBox->addItem(tr("/dev/ttyS1"),QVariant::fromValue(QString("/dev/ttyS1")));
    ui->comboBox->setCurrentIndex(0);  //set dev/ttyS0 default


    ui->comboBox_2->addItem("1200",QVariant::fromValue(BAUD1200));
    ui->comboBox_2->addItem("1800",QVariant::fromValue(BAUD1800));
    ui->comboBox_2->addItem("2400",QVariant::fromValue(BAUD2400));
    ui->comboBox_2->addItem("4800",QVariant::fromValue(BAUD4800));
    ui->comboBox_2->addItem("9600",QVariant::fromValue(BAUD9600));
    ui->comboBox_2->addItem("19.2K",QVariant::fromValue(BAUD19200));
    ui->comboBox_2->addItem("38.4K",QVariant::fromValue(BAUD38400));
    ui->comboBox_2->addItem("57.6K",QVariant::fromValue(BAUD57600));
    ui->comboBox_2->addItem("76.8K",QVariant::fromValue(BAUD76800));
    ui->comboBox_2->addItem("115.2K",QVariant::fromValue(BAUD115200));
    ui->comboBox_2->setCurrentIndex(6); //38.4 k default baud rate


    ui->comboBox_3->addItem("5",QVariant::fromValue(DATA_5));
    ui->comboBox_3->addItem("6",QVariant::fromValue(DATA_6));
    ui->comboBox_3->addItem("7",QVariant::fromValue(DATA_7));
    ui->comboBox_3->addItem("8",QVariant::fromValue(DATA_8));
    ui->comboBox_3->setCurrentIndex(3);   //8 bit


    ui->comboBox_4->addItem("None",QVariant::fromValue(PAR_NONE));
    ui->comboBox_4->addItem("EVEN",QVariant::fromValue(PAR_EVEN));
    ui->comboBox_4->addItem("ODD",QVariant::fromValue(PAR_ODD));
    ui->comboBox_4->setCurrentIndex(0);


    ui->comboBox_5->addItem("1",QVariant::fromValue(STOP_1));
    ui->comboBox_5->addItem("2",QVariant::fromValue(STOP_2));
    ui->comboBox_5->setCurrentIndex(0);

   // ui->textEdit->setText("Read Only Mode");

    QValidator *myvalidator =new QDoubleValidator ;
    ui->lineEdit_5->setValidator(myvalidator);
    ui->lineEdit_2->setValidator(myvalidator);
    ui->lineEdit_3->setValidator(myvalidator);
    ui->lineEdit_4->setValidator(myvalidator);
    //////////////////////////////////////////////////////
   //   QWTPLOT
    ///////////////////////////////////////////////////////
    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom,tr("Time"));
    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft,tr("Readings"));
    ui->qwtPlot->setCanvasBackground(Qt::white);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,ui->lineEdit_4->text().toInt());
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,ui->lineEdit_2->text().toInt(),
                              ui->lineEdit_3->text().toInt());
    this->setCentralWidget(ui->splitter);
    //connect()
    connect(&mytimer,SIGNAL(timeout()),this,SLOT(replot()));
    mytimer.start(15);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->groupBox->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    QVariant temp;
    QextSerialPort *port ;
    if(ui->checkBox->isChecked())
        port =new QextSerialPort(ui->lineEdit->text());
    else
    {
        temp =ui->comboBox->itemData(ui->comboBox->currentIndex());
                port =new QextSerialPort(temp.value<QString>());
    }
    port->setBaudRate(BAUD19200);
    port->setDataBits(DATA_8);
    port->setFlowControl(FLOW_OFF);
    port->setStopBits(STOP_1);
    port->setParity(PAR_NONE);
    if(port->open(QIODevice::ReadWrite))
        ui->label_6->setText("Successfully opened the port");
    else
        ui->label_6->setText("NotConnected!");
    recPort =new ReceivePort(port);
    connect(recPort,SIGNAL(BytesReceived_signal(QByteArray,int)),
            this,SLOT(received_signal(QByteArray,int)));
    connect(this,SIGNAL(datalinerec_signal(QString)),this,SLOT(updatedata(QString)));
    recPort->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    ReceivePort *temp =recPort ;
    recPort=NULL;
    delete temp ;
    ui->groupBox->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->label_6->setText("Not connected! open port");
}
void MainWindow::on_pushButton_4_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save file"),QDir::currentPath(),
                                                    tr("Data files(*.xcv *.txt) ;;ALL files (*.*)"));

      QFile file(filename);
           if (!file.open(QFile::WriteOnly | QFile::Text))
                   qDebug()<<"Failed to open file";
           QTextStream savestream(&file);
           savestream<<(ui->textEdit)->toPlainText();
           file.close();
}

void MainWindow::on_pushButton_5_clicked()
{
    double dummydata=0;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,ui->lineEdit_4->text().toInt());
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,ui->lineEdit_2->text().toInt(),
                              ui->lineEdit_3->text().toInt());
    this->noofsamples=ui->lineEdit_4->text().toInt();
    if(noofsamples>20000)
        noofsamples=20000;
    this->noofcurves=ui->lineEdit_5->text().toInt();
    if(noofcurves >10)
        noofcurves =10;
    for(int i=0 ;i<10;i++)
    {
        this->mycurves[i].setSamples(&dummydata,&dummydata,1);
        mycurves[i].attach(ui->qwtPlot);
    }
    QPen mypen ;
    for(int i=0 ;i<noofcurves;i++)
    {
        switch(i)
        {
        case 0:
            mypen =QPen(Qt::red);
                    break;
        case 1:
            mypen =QPen(Qt::blue);
                    break;
        case 2:
            mypen =QPen(Qt::green);
                    break;
        case 3:
            mypen =QPen(Qt::magenta);
                    break;
        case 4:
            mypen =QPen(Qt::cyan);
                    break;
        case 5:
            mypen =QPen(Qt::black);
                    break;
        case 6:
            mypen =QPen(Qt::darkYellow);
            mypen.setStyle(Qt::DotLine);
                    break;
        case 7:
            mypen =QPen(Qt::darkGray);
            mypen.setStyle(Qt::DotLine);
                    break;
        case 8:
            mypen =QPen(Qt::darkMagenta);
            mypen.setStyle(Qt::DotLine);
                    break;
        case 9:
            mypen =QPen(Qt::darkGreen);
            mypen.setStyle(Qt::DotLine);
                    break;
        }
        mypen.setWidthF(1);
        this->mycurves[i].setPen(mypen);
    }
}
void MainWindow::replot()
{
    ui->qwtPlot->replot();
}
void MainWindow::received_signal(const QByteArray &data, int num)
{
    for(int i=0 ;i<num;i++)
        recData.enqueue(data[i]);
    if(recData.size() >ui->lineEdit_6->text().toInt())
    {
        int i=0;
        while((ch=recData.dequeue())!='\n')
            datastring[i++]=ch;
        ui->textEdit->append(datastring);
        emit datalinerec_signal(datastring);
    }
}
void MainWindow::updatedata(QString str)
{
    QTextStream in(&str);
    for(int i=0;i<noofcurves;i++)
    {
        in>>y_data[i];
        in>>ch1;
    }
    for(int i=0;i<noofcurves;i++)
    {
        memmove(mycurvedata[i].data,&mycurvedata[i].data[1]
                    ,(noofsamples-1)*sizeof(double));
        mycurvedata[i].data[noofsamples-1]=y_data[i];
        this->mycurves[i].setSamples(xdata,mycurvedata[i].data,noofsamples);
    }
}
