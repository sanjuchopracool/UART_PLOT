#include "receiveport.h"

ReceivePort::ReceivePort(QextSerialPort *port)
{
    receiveport = port ;
    stopped =false;
}
void ReceivePort::run()
{
    int numbytes =0 ;
    char data[1024] ;
    QByteArray receivedData ;
    forever
    {
        if(stopped)
        {
            stopped=false;
            break;
        }
        receiveport->waitForReadyRead(1);
        numbytes = this->receiveport->bytesAvailable();
        if(numbytes > 0)
        {
            receivemutex.lock();
            receiveport->read(data,numbytes);
            receivedData =data ;
            receivemutex.unlock();
            emit BytesReceived_signal(receivedData,numbytes);
           // qDebug()<<data;
        }
    }

}
ReceivePort::~ReceivePort()
{
    stoprec();
    wait();
}
