#include <QCoreApplication>
#include "persontable.h"

/* Overload operator<< to write a Person-struct to stream.
 */
QDataStream &operator<<(QDataStream &out, const Person &a)
{
  out << a.iid << a.name << a.phone << a.country;
  return out;
}

/* Overload operator>> to read a Person-struct from stream.
 */
QDataStream &operator>>(QDataStream &in, Person &a)
{
  in >> a.iid >> a.name >> a.phone >> a.country;
  return in;
}

/* Person table constructor.
 * 1. Initializes a table's data.
 * 2. emits SendSync signal, to synchronize with external sources.
 */
PersonTable::PersonTable(QObject *parent)
  :QAbstractTableModel(parent)
{
  /* 1 */
  m_persons.append({1, "cock", 8888, 38});
  m_persons.append({2, "shit cock", 666, 1});

  /* 2 */
  connect(this, &PersonTable::dataChanged,
          this, [=]() {
    if (m_persons.size() < 1) {
      return;
    }
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    for (Person &it: m_persons) {
      stream << it;
    }

    emit sendSync(byteArray);
  });
}

/* receiveSync slot. To synchronization.
 * When occurs, table's data updates.
 */
void PersonTable::receiveSync(QByteArray bytes)
{
  /* read stream and place it's data to the temporary list(tmp_persons) */
  QDataStream stream(&bytes, QIODevice::ReadOnly);
  QList<Person> tmp_persons;
  Person p;
  while (!stream.atEnd()) {
      stream >> p;
      tmp_persons.append(p);
  }

  /* if the table's data do not equal. we should update it */
  if (tmp_persons != m_persons) {
    /* if we should delete a row */
    if (m_persons.size() > tmp_persons.size()) {
      /* walkthrough the temporary list and
         remove an absent item in the current list */
      for (int i = 0; i < tmp_persons.size(); ++i) {
        if (!(m_persons[i] == tmp_persons[i])) { // "a!=b" === "!(a == b)"
          removeRow(i);
          return;
        }
      }
      /* if the last item should be removed */
      removeRow(m_persons.size() - 1);
      return;
    } else
      /* if we should insert a row */
      if (m_persons.size() < tmp_persons.size()) {
        for (int i = 0; i < tmp_persons.size() - m_persons.size(); ++i) {
          add();
        }
        m_persons = tmp_persons;
        return;
    } else {
      /* size is equals, but some cells should be updated */
      m_persons = tmp_persons;
      QModelIndex indexFrom = createIndex(0, 0, static_cast<void *>(0));
      QModelIndex indexTo = createIndex(m_persons.size(), columnCount() - 1,
                                        static_cast<void *>(0));
      emit dataChanged(indexFrom, indexTo);
    }
  }
}

/* Overridden method, returns a count of rows (count of
 * a Persons in the list)
 */
int PersonTable::rowCount(const QModelIndex &parent) const
{
  (void) parent;
  return  m_persons.size();
}

/* Overridden method, returns a count of columns (count of qml roles)
 */
int PersonTable::columnCount(const QModelIndex &parent) const
{
  (void) parent;
  return  roleNames().size();
}

/* Overridden method. Returns a cell by index (the row is an index.row,
 * the column is a role)
 */
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

/* Inits and returns a hash of roles, paired with QML roles
 */
QHash<int, QByteArray> PersonTable::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles.insert(ID, "iid");
  roles.insert(NAME, "name");
  roles.insert(PHONE, "phone");
  roles.insert(COUNTRY, "country");
  return roles;
}

/* Adds an empty element to the table's data list
 */
void PersonTable::add()
{
  beginInsertRows(QModelIndex(), m_persons.size(), m_persons.size());
  m_persons.append({m_persons.size() + 1, "", 0, 0});
  endInsertRows();

  QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
  emit dataChanged(index, index);
}

/* Overridden method. Modifies a cell by index (the row is an index.row,
 * the column is a role)
 */
bool PersonTable::setData(const QModelIndex &index,
                          const QVariant &value, int role)
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

/* Overridden method, sets editable flag
 */
Qt::ItemFlags PersonTable::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
