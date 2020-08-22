#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include "global.h"

class Server : public QObject
{
  Q_OBJECT

public:
  explicit Server(QObject *parent = nullptr);
  virtual ~Server();
  void startListen(QHostAddress addr, int port);

  int sendData(QByteArray &);

public slots:
  void onNewConnection();
  void onSocketStateChanged(QAbstractSocket::SocketState socketState);
  QByteArray onReadyRead();

signals:
  void sendSync(QByteArray);

private:
  QTcpServer  _server;
  QList<QTcpSocket*>  _sockets;
};

#endif // SERVER_H
