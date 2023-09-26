/**
 * \file
 * \brief A File-descriptor management interface.
 */
#pragma once

/* toolchain */
#include <cassert>

/* internal */
#include "EpollManager.h"
#include "FdManager.h"
#include "Termios.h"
#include "file_descriptors.h"

namespace Viktor
{

class Viktor
{
  public:
    Viktor(FdManager &_fds, Epoll &_epoll, Termios &_terminal)
        : echo(true), fds(_fds), epoll(_epoll), terminal(_terminal)
    {
        /* Turn input echo and canonical mode off. */
        assert(terminal.set_echo(false));
        assert(terminal.set_canonical(false));

        /* Add input handling. */
        assert(epoll.add(terminal.fd, EPOLLIN));
        assert(
            epoll.event_handler(terminal.fd, [this](int fd, uint32_t events) {
                return input_handler(fd, events);
            }));
    }

    int run()
    {
        while (epoll.has_handlers())
        {
            epoll.run();
        }

        return 0;
    }

    bool input_handler(int fd, uint32_t events)
    {
        bool result = false;

        if (echo)
        {
            result = echo_handler(fd, events);
        }

        return result;
    }

    bool echo_handler(int fd, uint32_t events)
    {
        bool result = events & EPOLLIN;

        /* Read from the file descriptor. */
        if (result)
        {
            char data = '\0';
            while (read(fd, &data, 1) == 1 && result)
            {
                result = data != 'q';

                /* refactor this to not use std::cout (need our output fd) */
                std::cout << int(data);
                if (iscntrl(data))
                {
                    std::cout << " <cntrl>";
                }
                else
                {
                    std::cout << " (" << data << ")";
                }
                std::cout << std::endl;
            }
        }

        return result;
    }

    bool echo;

  protected:
    FdManager &fds;
    Epoll &epoll;
    Termios &terminal;
};

} // namespace Viktor
