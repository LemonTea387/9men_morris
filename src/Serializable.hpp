#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <string>
class Serializable {
  /**
   * The object should serialize itself into string.
   */
  virtual std::string serialize() = 0;
};

#endif
