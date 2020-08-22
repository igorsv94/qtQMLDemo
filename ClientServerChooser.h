#ifndef CLIENTSERVERCHOOSER_H
#define CLIENTSERVERCHOOSER_H

#include <QObject>
#include <QHostAddress>
#include <QDebug>

#include "server.h"
#include "client.h"

class ClientServerChooser
{

public:
  enum Type {
    SERVER = 0,
    CLIENT
  };
  ClientServerChooser(QHostAddress addr, int port)
  {
    qDebug() << __PRETTY_FUNCTION__;
    if (Client::serverIsAvaliable(addr, port)) {
      type = CLIENT;
      client = new Client();
      client->connectToServer(addr, port);
    } else {
      server = new Server();
      server->startListen(addr, port);
      type = SERVER;
    }
  };

  ~ClientServerChooser() { if (type == SERVER) delete server;
                           else delete client; }


private:
  Client *client;
  Server *server;
  Type   type;
};

#endif // CLIENTSERVERCHOOSER_H
