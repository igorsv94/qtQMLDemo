#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#include "global.h"

/* Very simple Client class,
 * that uses QTcpSocket and communicates with a server
 */
class Client : public QObject
{
  Q_OBJECT

public:
  explicit Client(QObject *parent = 0);
  virtual ~Client();

  void connectToServer(QHostAddress, int);
  static bool serverIsAvaliable(QHostAddress, int);

public slots:
  QByteArray onReadyRead();
  int  sendData(QByteArray &);
  void disconnect(QAbstractSocket::SocketState) { _socket.disconnectFromHost();
                                                  _isConnected = false; };
  void error(QAbstractSocket::SocketError) {};

signals:
  void sendSync(QByteArray);

private:
  QTcpSocket   _socket;
  QHostAddress _addr;
  int          _port;
  bool         _isConnected;
};

#endif // CLIENT_H
