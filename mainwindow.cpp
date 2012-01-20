#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMetaType>
#include<qextserialport.h>
#include<QValidator>
Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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

    ui->textEdit->setText("Read Only Mode");

    QValidator *myvalidator =new QDoubleValidator ;
    ui->lineEdit_5->setValidator(myvalidator);
    ui->lineEdit_2->setValidator(myvalidator);
    ui->lineEdit_3->setValidator(myvalidator);
    ui->lineEdit_4->setValidator(myvalidator);


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
    ui->label_6->setText("Connected!");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->groupBox->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->label_6->setText("Not connected! open port");
}
