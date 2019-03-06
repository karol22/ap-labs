#include <stdio.h>
#include "logger.h"

int main () {

    printf("Normal message\n");
    infof("INFO message\n");
    warnf("WARNING message\n");
    errorf("ERROR message\n");
    panicf("PANIC message\n");
    return 0;
}