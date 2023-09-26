/**
 * \file
 * \brief A File-descriptor management interface.
 */
#pragma once

/* internal */
#include "FdManager.h"
#include "file_descriptors.h"

namespace Viktor
{

class Viktor
{
  public:
    Viktor(FdManager &_fds) : fds(_fds)
    {
        epoll = fds["epoll"];
    }

    int run()
    {
        /* Start adding stuff to epoll. */
        (void)epoll;
        std::cout << epoll << std::endl;
        // epoll_ctl(epoll, 0, );

        return 0;
    }

  protected:
    FdManager &fds;
    int epoll;
};

} // namespace Viktor
