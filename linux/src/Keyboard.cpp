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

void Keyboard::run() {
  while (1) {
    auto key = static_cast<unsigned int>(backend->wait());

    send_key_event(uinput_fd, key);
  }
}
