#include <stdio.h>
#include <stdarg.h>
#include "logger.h"

#define REDFONT 		printf("\033[1;31m");
#define PURPLEFONT 		printf("\033[0;35m");
#define YELLOWFONT 		printf("\033[1;33m");
#define GREENFONT 		printf("\033[0;32m");
#define DEFAULTFONT 	printf("\033[0m");

int errorf(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	REDFONT
	status = printf(format, args);
	DEFAULTFONT
    return status;
}

int infof(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	GREENFONT
	status = printf(format, args);
	DEFAULTFONT
    return status;
}

int warnf(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	YELLOWFONT
	status = printf(format, args);
	DEFAULTFONT
    return status;
}

int panicf(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	PURPLEFONT
	status = printf(format, args);
	DEFAULTFONT
    return status;
}