#include "Keyboard.h"
#include "Backend.h"

#include <memory>

#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <unordered_map>

namespace {

/* Setup the uinput device */
int setup_uinput_device() {
  int uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if (uinp_fd == 0) {
    printf("Unable to open /dev/uinput\n");
    return -1;
  }

  // Setup the uinput device
  ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
  ioctl(uinp_fd, UI_SET_EVBIT, EV_SYN);

  // ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);

  int i;
  for (i = 0; i < 256; i++) {
    if (ioctl(uinp_fd, UI_SET_KEYBIT, i) < 0) {
      printf("set keybit error\n");
    }
  }

  struct uinput_setup uinp;
  memset(&uinp, 0, sizeof(uinp)); // Intialize the uInput device to NULL
  // strncpy(uinp.name, "Virtual Keyboard Device", strlen("Virtual Keyboard
  // Device"));
  uinp.id.bustype = BUS_USB;
  uinp.id.product = 0x1234;
  uinp.id.vendor = 0x5678;
  strcpy(uinp.name, "arduino keypad");

  /* Create input device into input sub-system */
  ioctl(uinp_fd, UI_DEV_SETUP, &uinp);

  if (ioctl(uinp_fd, UI_DEV_CREATE)) {
    printf("Unable to create UINPUT device.");
    return -1;
  }

  return uinp_fd;
}

void emit(int fd, int type, int code, int val) {
  struct input_event ie;

  ie.type = type;
  ie.code = code;
  ie.value = val;
  /* timestamp values below are ignored */
  ie.time.tv_sec = 0;
  ie.time.tv_usec = 0;

  write(fd, &ie, sizeof(ie));
}

void send_key_event(int fd, unsigned int keycode) {
  emit(fd, EV_KEY, keycode, 1);
  emit(fd, EV_SYN, SYN_REPORT, 0);
  emit(fd, EV_KEY, keycode, 0);
  emit(fd, EV_SYN, SYN_REPORT, 0);
}

void destroy_uinput_device(int uinp_fd) {
  /* Destroy the input device */
  ioctl(uinp_fd, UI_DEV_DESTROY);
  /* Close the UINPUT device */
  close(uinp_fd);
}

} // namespace

Keyboard::Keyboard(std::unique_ptr<Backend> backend_)
    : backend(std::move(backend_)) {
  uinput_fd = setup_uinput_device();
}

Keyboard::~Keyboard() { destroy_uinput_device(uinput_fd); }

const std::unordered_map<Keyset, unsigned long> map = {
    {Keyset::key_0, KEY_0}, {Keyset::key_1, KEY_1}, {Keyset::key_2, KEY_2},
    {Keyset::key_3, KEY_3}, {Keyset::key_4, KEY_4}, {Keyset::key_5, KEY_5},
    {Keyset::key_6, KEY_6}, {Keyset::key_7, KEY_7}, {Keyset::key_8, KEY_8},
    {Keyset::key_9, KEY_9}, {Keyset::key_A, KEY_A}, {Keyset::key_B, KEY_B},
    {Keyset::key_C, KEY_C}, {Keyset::key_D, KEY_D}, {Keyset::key_E, KEY_E},
    {Keyset::key_F, KEY_F},
};

void Keyboard::run() {
  while (1) {
    auto key = backend->wait();

    send_key_event(uinput_fd, map.at(key));
  }
}
