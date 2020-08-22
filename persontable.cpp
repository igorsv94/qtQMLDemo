#include "persontable.h"

PersonTable::PersonTable(QObject *parent)
  :QAbstractTableModel(parent)
{
  m_persons.append({1, "cock", 8888, 38});
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
