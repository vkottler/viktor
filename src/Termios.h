/**
 * \file
 * \brief An interface to termios.
 */
#pragma once

/* linux */
#include <termios.h>

/* toolchain */
#include <iostream>

namespace Viktor
{

class Termios
{
  public:
    static constexpr int default_action = TCSAFLUSH;

    Termios(int _fd);
    ~Termios();

    void info(std::ostream &stream = std::cout);

    bool make_raw(int optional_actions = default_action);

    bool set_echo(bool state, int optional_actions = default_action);
    bool set_canonical(bool state, int optional_actions = default_action);

    const int fd;

  protected:
    bool valid;
    struct termios original;
    struct termios current;

    bool setattrs(int optional_actions = default_action);
};

} // namespace Viktor
