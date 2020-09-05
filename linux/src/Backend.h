#ifndef BACKEND_H
#define BACKEND_H

#include "Keyset.h"

class Backend {
public:
  Backend() = default;
  virtual ~Backend() = default;
  virtual Keyset wait() = 0;
};

#endif /* BACKEND_H */
