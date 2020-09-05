#ifndef SERIALBACKEND_H
#define SERIALBACKEND_H

#include "Backend.h"
#include "Keyset.h"

#include <string>

class SerialBackend : public Backend {
public:
  SerialBackend(std::string name);
  ~SerialBackend() override;
  virtual Keyset wait() override;

private:
  int serial_fd = 0;
};

#endif /* SERIALBACKEND_H */
