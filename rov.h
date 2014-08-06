#ifndef ROV_H
#define ROV_H

#include <QObject>
#include <QTcpSocket>

#define REQ_GO_FORWARD 0x01
#define REQ_GO_BACKWARD 0x02

class ROV : public QObject
{
  Q_OBJECT

public:
  explicit ROV(QObject *parent = 0);

signals:
  void connected();
  void disconnected();

public slots:
  bool connectToRobot();
  void interpretButton(int index, bool status);
  void interpretAxis(int index, qint16 value);

private slots:
  void sendRequest(char function, float *arguments, int size);
  void tcpConnected();
  void tcpDisconnected();
  void readRequest();
private:
  QTcpSocket *tcpSocket;

};

#endif // ROV_H
