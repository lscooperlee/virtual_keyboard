#ifndef EMIKEYBOARD_H
#define EMIKEYBOARD_H

#include "Frontend.h"

#include <emi/emi.h>
#include <memory>

class Backend;

class EmiKeyboard : public Frontend {
public:
  EmiKeyboard(std::unique_ptr<Backend>, eu32 msg_);
  ~EmiKeyboard() override;
  void run() override;

private:
  std::unique_ptr<Backend> backend = {};
  eu32 msg = {};
};

#endif /*EMIKEYBOARD_H*/
