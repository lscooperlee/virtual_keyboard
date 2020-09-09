#include "SerialBackend.h"
#include "Keyset.h"

#include <stdexcept>
#include <unordered_map>

// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

namespace {
int serial_setup(const char *serial_device) {

  int serial_port = open(serial_device, O_RDWR);
  if (serial_port < 0) {
    printf("failed to open %s\n", serial_device);
    return -1;
  }

  struct termios tty = {};

  if (tcgetattr(serial_port, &tty) != 0) {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    return -1;
  }

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in

  // communication (most common)
  tty.c_cflag |= CS8; // 8 bits per byte (most common)

  // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag &= ~CRTSCTS;
  // Turn on READ & ignore ctrl lines (CLOCAL = 1)
  tty.c_cflag |= CREAD | CLOCAL;

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;   // Disable echo
  tty.c_lflag &= ~ECHOE;  // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG;   // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl

  // Disable any special handling of received bytes
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

  // Prevent special interpretation of output bytes (e.g.  // newline chars)
  tty.c_oflag &= ~OPOST;
  // Prevent conversion of newline to carriage return/line feed
  tty.c_oflag &= ~ONLCR;

  tty.c_cc[VTIME] = 0;
  tty.c_cc[VMIN] = 1;

  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    return -1;
  }

  return serial_port;
}

} // namespace

SerialBackend::SerialBackend(std::string name) {
  serial_fd = serial_setup(name.c_str());

  if (serial_fd < 0) {
    throw std::runtime_error("serial init failed");
  }
}

SerialBackend::~SerialBackend() { close(serial_fd); }

Keyset SerialBackend::wait() {

  const std::unordered_map<char, Keyset> map = {
      {'0', Keyset::key_0}, {'1', Keyset::key_1}, {'2', Keyset::key_2},
      {'3', Keyset::key_3}, {'4', Keyset::key_4}, {'5', Keyset::key_5},
      {'6', Keyset::key_6}, {'7', Keyset::key_7}, {'8', Keyset::key_8},
      {'9', Keyset::key_9}, {'A', Keyset::key_A}, {'B', Keyset::key_B},
      {'C', Keyset::key_C}, {'D', Keyset::key_D},
  };

  char key;
  auto n = read(serial_fd, &key, sizeof(key));
  if (n < 0) {
    return Keyset::key_esc;
  }

  try {
    return map.at(key);
  } catch (const std::out_of_range &) {
    return Keyset::key_esc;
  }
}
