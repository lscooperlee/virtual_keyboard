#include "Keyboard.h"
#include "Keyset.h"
#include "SerialBackend.h"

#include <memory>

int main(int argc, char **argv) {

  Keyboard keyboard(std::make_unique<SerialBackend>("/dev/ttyUSB0"));

  keyboard.run();

  return 0;
}
