#ifndef RECEIVEPORT_H
#define RECEIVEPORT_H
//#include "files/qextserialport.h"
#include<qextserialport.h>
#include <QMutex>
#include<QDebug>
#include<QThread>
class ReceivePort :public QThread
{
    Q_OBJECT
private:
    QextSerialPort *receiveport ;
    QMutex receivemutex ;
    bool stopped;

public:
    ReceivePort(QextSerialPort *port);
    ~ReceivePort();
    void stoprec()
    {
        stopped =true;
    }

protected:
    void run();
signals:
    void BytesReceived_signal(const QByteArray &data,int num);
};

#endif // RECEIVEPORT_H
