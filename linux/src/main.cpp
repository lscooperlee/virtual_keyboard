#include "EmiKeyboard.h"
#include "Keyboard.h"
#include "Keyset.h"
#include "SerialBackend.h"

#include <memory>

int main(int argc, char **argv) {

  const char *name;

  if (argc >= 2) {
    name = argv[1];
  } else {
    name = "/dev/ttyUSB0";
  }

  EmiKeyboard keyboard(std::make_unique<SerialBackend>(name), 101);

  keyboard.run();

  return 0;
}
