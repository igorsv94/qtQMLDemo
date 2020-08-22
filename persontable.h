#ifndef PERSONTABLE_H
#define PERSONTABLE_H

#include <QAbstractTableModel>
#include <QList>
#include <QDebug>
#include <QDataStream>

#include "global.h"

class PersonTable: public QAbstractTableModel
{
  Q_OBJECT

public:
  enum Roles {
    ID = 0,
    NAME,
    PHONE,
    COUNTRY
  };
  explicit PersonTable(QObject *parent = nullptr);

  Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

  Q_INVOKABLE void updateCell(int index, QVariant val, int role) {
    auto ind = QAbstractTableModel::index(index, role);
    this->setData(ind, val, role);
  }

  Q_INVOKABLE void removeRow(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    m_persons.removeAt(row);
    endRemoveRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
  }

  Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

  Q_INVOKABLE void add();

public slots:
  void receiveSync(QByteArray);

signals:
  void sendSync(QByteArray bytes);

private:
  QList<Person> m_persons;
};


#endif // PERSONTABLE_H
