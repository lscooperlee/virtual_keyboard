#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Keyset.h"

#include <memory>

class Backend;

class Keyboard {
public:
  Keyboard(std::unique_ptr<Backend>);
  virtual ~Keyboard();
  void run();

private:
  std::unique_ptr<Backend> backend = {};
  int uinput_fd = 0;
};

#endif /*KEYBOARD_H*/
