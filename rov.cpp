#include "rov.h"

ROV::ROV(QObject *parent) :
  QObject(parent)
{
  tcpSocket = new QTcpSocket(this);
  connect(tcpSocket,SIGNAL(connected()),
          this,
          SLOT(tcpConnected()));
  connect(tcpSocket,SIGNAL(disconnected()),
          this,SLOT(tcpDisconnected()));

  connect(tcpSocket,SIGNAL(readyRead()),
          this,SLOT(readRequest()));
}

bool ROV::connectToRobot(){
  tcpSocket->connectToHost("192.168.1.121",3000);
  return tcpSocket->waitForConnected(3000);
}

void ROV::interpretButton(int index, bool status){

  //Tutaj interpretujesz przyciski i odpowiednią funkce wysylasz sendRequest(...) po 2 stronie trzeba ja zinterpretowac
  qDebug()<<"interpretButton"<<index<<" "<<status;
}

void ROV::interpretAxis(int index, qint16 value){

  //To samo co guziki tylko dla osi
  qDebug()<<"interpretAxis"<<index<<" "<<value;
}

void ROV::tcpConnected(){
  emit connected();
  qDebug()<<"Connected";
}

void ROV::tcpDisconnected(){
  emit disconnected();
}

void ROV::sendRequest(char function, float *arguments, int size){
  QByteArray array;
  array.push_back(0x55);
  array.push_back(function);
  array.push_back(size);
  for(int i=0;i<size;i++)
    array.append(reinterpret_cast<char *> (&arguments[i]),sizeof(float));

  array.push_back(0xAA);

  tcpSocket->write(array);
}

void ROV::readRequest()
{
  qDebug()<<"Reading";
}
