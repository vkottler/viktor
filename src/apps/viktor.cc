/**
 * \file
 * \brief Program entry.
 */

/* linux */
#include <sys/epoll.h>

/* toolchain */
#include <cassert>

/* internal */
#include "../FdManager.h"
#include "../Viktor.h"
#include "../text.h"

/**
 * Run the application.
 *
 * \return 0 on success.
 */
int main(void)
{
    using namespace Viktor;

    int result;

    {
        FdManager fds;

        /*
         * Create the event-poll interface.
         */
        int epoll = epoll_create1(EPOLL_CLOEXEC);
        assert(epoll != -1);
        fds.add_fd("epoll", epoll);

        /*
         * Run the application.
         */
        ::Viktor::Viktor app(fds);
        result = app.run();
    }

    print_verb_name_condition("viktor", "run", result == 0);
    return result;
}
