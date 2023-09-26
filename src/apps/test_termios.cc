/* toolchain */
#include <cstdio>

/* internal */
#include "../Termios.h"

using namespace Viktor;

int main(void)
{
    {
        Termios term(fileno(stdin));
        term.info();
    }
    return 0;
}
