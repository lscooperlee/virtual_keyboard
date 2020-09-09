#ifndef FRONTEND_H
#define FRONTEND_H

#include <memory>

class Backend;

class Frontend {
public:
  virtual ~Frontend() = default;
  virtual void run() = 0;
};

#endif /*FRONTEND_H*/
