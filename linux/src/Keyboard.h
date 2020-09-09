#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Frontend.h"

#include <memory>

class Backend;

class Keyboard : public Frontend {
public:
  Keyboard(std::unique_ptr<Backend>);
  ~Keyboard() override;
  void run() override;

private:
  std::unique_ptr<Backend> backend = {};
  int uinput_fd = 0;
};

#endif /*KEYBOARD_H*/
