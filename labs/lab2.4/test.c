#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

void init_log()
{
    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog("testd",LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
}

int main(void) {

    init_log();
    printf("Sessiotarted!");
    syslog(LOG_NOTICE, "\033[1;31mholahola!!");
    closelog();

    return EXIT_SUCCESS;
}