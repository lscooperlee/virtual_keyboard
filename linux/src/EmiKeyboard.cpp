#include "EmiKeyboard.h"
#include "Backend.h"

#include <memory>

EmiKeyboard::EmiKeyboard(std::unique_ptr<Backend> backend_, eu32 msg_)
    : backend(std::move(backend_)), msg(msg_) {}

EmiKeyboard::~EmiKeyboard() {}

void EmiKeyboard::run() {
  while (1) {
    auto key = static_cast<eu32>(backend->wait());

    auto e_msg = make_emi_msg("127.0.0.1", msg, key);
    emi_msg_send(e_msg);
  }
}
