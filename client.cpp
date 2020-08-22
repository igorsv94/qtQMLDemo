#include "client.h"

#include <QObject>
#include <QDebug>
#include <QHostAddress>

Client::Client(QObject *parent) :
  QObject(parent),
  _isConnected(false)
{
  qDebug() << __PRETTY_FUNCTION__ ;
}

Client::~Client()
{
}

void Client::connectToServer(QHostAddress addr, int port)
{
  if (_socket.state() != QTcpSocket::ConnectedState) {
    _socket.connectToHost(addr, port);
    if (!_socket.waitForConnected(2000)) {
      return;
    }
    _isConnected = true;
    connect(&_socket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));
    connect(&_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(disconnect(QAbstractSocket::SocketState)));
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(error(QAbstractSocket::SocketError)));
  }
}

bool Client::serverIsAvaliable(QHostAddress addr, int port)
{
  QTcpSocket socket;
  socket.connectToHost(addr, port);
  if (!socket.waitForConnected(2000)) {
    return false;
  }

  return true;
}

QByteArray Client::onReadyRead()
{
  QByteArray bytes = _socket.readAll();
  qDebug() << bytes;
  return bytes;
}

int Client::sendData(QByteArray &bytes)
{
  if (!_isConnected) {
    return 0;
  }

  return _socket.write(bytes);
}
