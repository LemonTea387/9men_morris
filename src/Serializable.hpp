#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <string>
class Serializable {
  virtual std::string serialize() = 0;
};

#endif
