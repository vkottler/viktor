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
        Epoll epoll;

        /*
         * Create the terminal interface.
         */
        Termios term(fileno(stdin));
        assert(fd_set_blocking_state(fileno(stdout)));

        /*
         * Run the application.
         */
        ::Viktor::Viktor app(fds, epoll, term);
        result = app.run();
    }

    print_verb_name_condition("viktor", "run", result == 0);
    return result;
}
