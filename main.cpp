#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "persontable.h"
#include "ClientServerChooser.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);

//  qRegisterMetaTypeStreamOperators<Person>("Person");
  ClientServerChooser *chooser = new
      ClientServerChooser(QHostAddress::LocalHost, 4242);
  (void) chooser;

  PersonTable *persons = new PersonTable;

  QObject::connect(chooser, &ClientServerChooser::receiveSync,
                   persons, &PersonTable::receiveSync);

  QObject::connect(persons, &PersonTable::sendSync,
          chooser, &ClientServerChooser::sendSync);

  engine.rootContext()->setContextProperty("persons", persons);
  engine.load(url);

  return app.exec();
}
