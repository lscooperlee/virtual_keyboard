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

  key_Q = KEY_Q,
  key_W = KEY_W,
  key_E = KEY_E,
  key_R = KEY_R,
  key_T = KEY_T,
  key_Y = KEY_Y,
  key_U = KEY_U,
  key_I = KEY_I,
  key_O = KEY_O,
  key_P = KEY_P,

  key_A = KEY_A,
  key_S = KEY_S,
  key_D = KEY_D,
  key_F = KEY_F,
  key_G = KEY_G,
  key_H = KEY_H,
  key_J = KEY_J,
  key_K = KEY_K,
  key_L = KEY_L,

  key_Z = KEY_Z,
  key_X = KEY_X,
  key_C = KEY_C,
  key_V = KEY_V,
  key_B = KEY_B,
  key_N = KEY_N,
  key_M = KEY_M,

  //key_star = KEY_NUMERIC_STAR,
  //key_pound = KEY_NUMERIC_POUND,
};

#endif /* KEYSET_H */
