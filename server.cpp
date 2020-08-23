#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>

#include "server.h"

Server::Server(QObject *parent) :
  QObject(parent),
  _server(this)
{
}

Server::~Server()
{

}

void Server::startListen(QHostAddress addr, int port)
{
  _server.listen(addr, port);
  connect(&_server, SIGNAL(newConnection()),
          this, SLOT(onNewConnection()));
}

int Server::sendData(QByteArray &bytes)
{
  for (QTcpSocket* socket : _sockets) {
    return socket->write(bytes);
  }
  return -1;
}

void Server::onNewConnection()
{
 QTcpSocket *clientSocket = _server.nextPendingConnection();
 connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
 connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
         this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

  _sockets.push_back(clientSocket);
}

void Server::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
  if (socketState == QAbstractSocket::UnconnectedState) {
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    _sockets.removeOne(sender);
  }
}

QByteArray Server::onReadyRead()
{
  QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
  QByteArray bytes = sender->readAll();

  emit sendSync(bytes);
  return bytes;
}
