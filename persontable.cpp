#include <QCoreApplication>
#include "persontable.h"

QDataStream &operator<<(QDataStream &out, const Person &a)
{
  out << a.iid;
  out << a.name;
  out << a.phone;
  out << a.country;
  return out;
}

QDataStream &operator>>(QDataStream &in, Person &a)
{
  in >> a.iid;
  in >> a.name;
  in >> a.phone;
  in >> a.country;
  return in;
}

PersonTable::PersonTable(QObject *parent)
  :QAbstractTableModel(parent)
{
  connect(this, &PersonTable::dataChanged,
          this, [=]() {
    if (m_persons.size() < 1) {
      return;
    }
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

//    stream << m_persons;
    qDebug() << "\nlambda";
    int i = 0;
    for (Person &it: m_persons) {
//      stream << it.iid << it.name << it.phone << it.country;
      stream << it;
      qDebug() << QCoreApplication::applicationPid() << "[" << i++ << "]: " << it.iid << it.name;
    }

    emit sendSync(byteArray);
  });

  m_persons.append({1, "cock", 8888, 38});
  m_persons.append({2, "shit cock", 666, 1});
}

void PersonTable::receiveSync(QByteArray bytes)
{
  QDataStream stream(&bytes, QIODevice::ReadOnly);
  QList<Person> tmp_persons;

  while( !stream.atEnd() ) {
      Person p;
      stream >> p;
      tmp_persons.append( p );
  }

  qDebug() << "\nreceiveSync:";
  if (tmp_persons != m_persons) {

    if (m_persons.size() > tmp_persons.size()) {
      for (int i = 0; i < tmp_persons.size(); ++i) {
        if (!(m_persons[i] == tmp_persons[i])) {
          removeRow(i);
          return;
        }
      }
      removeRow(m_persons.size() - 1);
      return;
    } else if (m_persons.size() < tmp_persons.size()) {
      for (int i = 0; i < tmp_persons.size() - m_persons.size(); ++i) add();
      m_persons = tmp_persons;
      return;
    } else {//equals
      qDebug() << "edit same size" << m_persons.size();
      m_persons = tmp_persons;
    }
    QModelIndex indexFrom = createIndex(0, 0, static_cast<void *>(0));
    QModelIndex indexTo = createIndex(m_persons.size(), columnCount() - 1, static_cast<void *>(0));
    qDebug() << "indexex: form:" << indexFrom << ", to " << indexTo;
    emit dataChanged(indexFrom, indexTo);
  }
}

int PersonTable::rowCount(const QModelIndex &parent) const
{
  (void) parent;
  return  m_persons.size();
}

int PersonTable::columnCount(const QModelIndex &parent) const
{
  (void) parent;
  return  roleNames().size();
}

QVariant PersonTable::data(const QModelIndex &index, int role) const
{
  QVariant variant;
  const int row = index.row();
  const int col = role;

  switch (col) {
  case ID:
    variant = m_persons.at(row).iid;
    break;
  case NAME:
    variant = m_persons.at(row).name;
    break;
  case PHONE:
    variant = m_persons.at(row).phone;
    break;
  case COUNTRY:
    variant = m_persons.at(row).country;
    break;
  }

  return variant;
}

QHash<int, QByteArray> PersonTable::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles.insert(ID, "iid");
  roles.insert(NAME, "name");
  roles.insert(PHONE, "phone");
  roles.insert(COUNTRY, "country");
  return roles;
}

void PersonTable::add()
{
  beginInsertRows(QModelIndex(), m_persons.size(), m_persons.size());
  m_persons.append({m_persons.size() + 1, "", 0, 0});
  endInsertRows();

  QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
  emit dataChanged(index, index);
}

bool PersonTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid()) {
    qWarning() << "index is invalid";
    return false;
  }

  switch (role) {
  case ID:
    m_persons[index.row()].iid = value.toInt();
    break;
  case NAME:
    m_persons[index.row()].name = value.toString();
    break;
  case PHONE:
    m_persons[index.row()].phone = value.toInt();
    break;
  case COUNTRY:
    m_persons[index.row()].country = value.toInt();
    break;

  default:
    return false;
  }

  emit dataChanged(index, index);

  return true;
}

Qt::ItemFlags PersonTable::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
