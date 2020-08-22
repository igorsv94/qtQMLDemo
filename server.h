#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

class Server : public QObject
{
  Q_OBJECT

public:
  explicit Server(QObject *parent = nullptr);
  ~Server();
  void startListen(QHostAddress addr, int port);

public slots:
  void onNewConnection();
  void onSocketStateChanged(QAbstractSocket::SocketState socketState);
  QByteArray onReadyRead();
private:
  QTcpServer  _server;
  QList<QTcpSocket*>  _sockets;
};

#endif // SERVER_H
