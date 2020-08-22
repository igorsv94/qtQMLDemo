#ifndef PERSONTABLE_H
#define PERSONTABLE_H

#include <QAbstractTableModel>
#include <QList>
#include <QDebug>

struct Person {
  enum Country{
    Russia = 8,
    USA = 1,
    Ukraine = 38
  };

  int32_t iid;
  QString name;
  uint64_t phone;
  int32_t country;
};

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

//protected:
  Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
//  Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

  Q_INVOKABLE void updateCell(int index, QVariant val, int role) {
//    qDebug() << "updateCell values:" << index << val << role;

    auto ind = QAbstractTableModel::index(index, role);
//    qDebug() << "index:" << ind;

    this->setData(ind, val, role);
  }

  Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  Q_INVOKABLE void add();

private:
  QList<Person> m_persons;
};


#endif // PERSONTABLE_H
