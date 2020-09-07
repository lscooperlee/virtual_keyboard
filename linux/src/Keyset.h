#ifndef KEYSET_H
#define KEYSET_H

#include <linux/input.h>

enum class Keyset {
  key_1 = KEY_1,
  key_2 = KEY_2,
  key_3 = KEY_3,
  key_4 = KEY_4,
  key_5 = KEY_5,
  key_6 = KEY_6,
  key_7 = KEY_7,
  key_8 = KEY_8,
  key_9 = KEY_9,
  key_0 = KEY_0,

  key_A = KEY_A,
  key_B = KEY_B,
  key_C = KEY_C,
  key_D = KEY_D,

  key_esc = KEY_ESC,
};

#endif /* KEYSET_H */
