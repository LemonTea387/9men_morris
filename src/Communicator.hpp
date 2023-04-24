#ifndef COMM_H
#define COMM_H

namespace Comm {
class Communicator {
 public:
  virtual void Notified(std::pair<int, int>);
};
}  // namespace Comm
#endif