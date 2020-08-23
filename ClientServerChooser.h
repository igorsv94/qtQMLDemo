#ifndef CLIENTSERVERCHOOSER_H
#define CLIENTSERVERCHOOSER_H

#include <QObject>
#include <QHostAddress>
#include <QDebug>

#include "server.h"
#include "client.h"

/* Client-Server chooser.
 * Selects a type of application (client or server).
 * Sends synchronization's data between client and server.
 */
class ClientServerChooser: public QObject
{
  Q_OBJECT

public:
  enum Type {
    SERVER = 0,
    CLIENT
  };
  ClientServerChooser(QHostAddress addr, int port, QObject *parent = nullptr)
    :QObject(parent)
  {
    if (Client::serverIsAvaliable(addr, port)) {
      type = CLIENT;
      client = new Client();
      client->connectToServer(addr, port);

      connect(client, &Client::sendSync,
              this, &ClientServerChooser::receiveSync);
    } else {
      type = SERVER;
      server = new Server();
      server->startListen(addr, port);

      connect(server, &Server::sendSync,
              this, &ClientServerChooser::receiveSync);
    }
  };

  virtual ~ClientServerChooser()
  {
    if (type == SERVER) delete server;
    else delete client;
  }

public slots:
  void sendSync(QByteArray bytes) {
    if (type == SERVER) {
      server->sendData(bytes);
    } else {
      client->sendData(bytes);
    }
  }

signals:
  void receiveSync(QByteArray);

private:
  Client *client;
  Server *server;
  Type   type;
};

#endif // CLIENTSERVERCHOOSER_H
