#include "Keyboard.h"
#include "Keyset.h"
#include "SerialBackend.h"

#include <memory>

int main(int argc, char **argv) {
  
  const char *name;
  
  if(argc >= 2){
      name = argv[1];
  }else{
      name = "/dev/ttyUSB0";
  }

  Keyboard keyboard(std::make_unique<SerialBackend>(name));

  keyboard.run();

  return 0;
}
