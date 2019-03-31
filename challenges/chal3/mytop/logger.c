#include <stdio.h>
#include <string.h>
#include "logger.h"
#include <stdarg.h>
#include <string.h>
#include <syslog.h>

int SYSLOG = 0;

int initLogger(char *logType) {
    printf("Initializing Logger on: %s\n", logType);
    if(strcmp(logType, "syslog") == 0) {
        SYSLOG = 1;
    } else {
		SYSLOG = 0;
		if(strcmp(logType, "stdout") != 0) return 1;
	}
    return 0;
}


int errorf(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	if(SYSLOG != 1){
		printf("\033[1;31m");
		status = vprintf(format, args);
		printf("\033[0m");
	} else {
		
		openlog("LOG-ERROR", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL1); 
		syslog(LOG_NOTICE, "\033[1;31m");
		vsyslog(LOG_INFO, format, args);
    	syslog(LOG_NOTICE, "\033[0m");
    	closelog();
	}
    return status;
}

int infof(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	if(SYSLOG != 1){
		printf("\033[0;32m");
		status = vprintf(format, args);
		printf("\033[0m");
	} else {
		openlog("LOG-INFO", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL1); 
		syslog(LOG_NOTICE, "\033[1;32m");
		vsyslog(LOG_INFO, format, args);
    	syslog(LOG_NOTICE, "\033[0m");
    	closelog();
	}
    return status;
}

int warnf(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	if(SYSLOG != 1){
		printf("\033[1;33m");
		status = vprintf(format, args);
		printf("\033[0m");
	} else {
		openlog("LOG-WARN", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL1); 
		syslog(LOG_NOTICE, "\033[1;33m");
		vsyslog(LOG_INFO, format, args);
    	syslog(LOG_NOTICE, "\033[0m");
    	closelog();
	}
    return status;
}

int panicf(const char *format, ...) {
	int status;
	va_list args;
	va_start(args, format);
	if(SYSLOG != 1){
		printf("\033[1;31m");
		status = vprintf(format, args);
		printf("\033[0m");
	} else {
		openlog("LOG-PANIC", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL1); 
		syslog(LOG_NOTICE, "\033[1;31m");
		vsyslog(LOG_INFO, format, args);
    	syslog(LOG_NOTICE, "\033[0m");
    	closelog();
	}
	
    return status;
}


