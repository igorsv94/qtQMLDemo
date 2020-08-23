#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

/* Basic struct for tableView
 */
struct Person {
//  enum Country{
//    Russia = 8,
//    USA = 1,
//    Ukraine = 38
//  };

  int32_t iid;
  QString name;
  uint64_t phone;
  int32_t country;

  bool operator==(Person &p) {
    return iid == p.iid && name == p.name &&
        phone == p.phone && country == p.country;
  }
};

#endif // GLOBAL_H
