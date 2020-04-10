#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

int init_logger(logger_t* logger, const char *log_file) {
    if (NULL == logger) {
        return -1;
    }
    logger->mode = CHECK_MODE;
    logger->log_file = fopen(log_file, "w+");
    logger->file_line_f = 1;
    return 0;
}

void _log(const char* __file__, unsigned long __line__, mode_e this_mode, const char *format, va_list arg) {

    char buf[FILE_LINE_SIZE + MODE_SIZE + MSG_SIZE];
    int len = 0;
    
    if ()


    switch (this_mode) {
        case INFO_MODE:
            len = snprintf(buf, PRE_SIZE, "[%5s] ", "INFO");
            break;
        case DEBUG_MODE:
            len = snprintf(buf, PRE_SIZE, "[%5s] ", "DEBUG");
            break;
        case CHECK_MODE:
            len = snprintf(buf, PRE_SIZE, "[%5s] ", "CHECK");
            break;
        case WARN_MODE:
            len = snprintf(buf, PRE_SIZE, "[%5s] ", "WARN");
            break;
        case ERROR_MODE:
            len = snprintf(buf, PRE_SIZE, "[%5s] ", "ERROR");
            break;
    }

    plen = vsnprintf(buf+PRE_SIZE-1, LOG_SIZE-1, format, arg);

    if (NULL != logger.log_file) {
        fwrite(buf, PRE_SIZE-1+plen, 1, logger.log_file);
    }

    if (this_mode >= logger.mode) {
        printf("%s", buf);
    }
}


void INFO(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(INFO_MODE, format, arg);
}

void DEBUG(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(DEBUG_MODE, format, arg);
}

void CHECK(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(CHECK_MODE, format, arg);
}


void WARN(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(WARN_MODE, format, arg);
}

void ERROR(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(ERROR_MODE, format, arg);
}
