#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

extern LOGGER logger;

Logger *
logger_new(const char *file)
{
    Logger *logger = (Logger *)maloc(sizeof(Logger));
    if (!logger) {
        perror("Fail to malloc logger.\n");
        return NULL;
    }
    memset(logger, 0, sizeof(Logger));

    memcpy(logger->file, file, sizeof(logger->file));
    logger->fp = fopen(logger->file, "w");
    if (!logger->fp) {
        perror("Fail to open file %s.\n", logger->file);
        return NULL;
    }

    return logger;
}

void _log(const char* __file__, unsigned long __line__, LOG_MODE mode, const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);

    char buf[FILE_LINE_SIZE + MODE_SIZE + MSG_SIZE];
    int len = 0;
    
    if (logger.is_file_line_on) {
        len += snprintf(buf, FILE_LINE_SIZE, "%5s: %5lu ", __file__, __line__);
    }


    switch (mode) {
        case INFO_MODE:
            len += snprintf(buf+len, MODE_SIZE, "[%5s] ", "INFO");
            break;
        case DEBUG_MODE:
            len += snprintf(buf+len, MODE_SIZE, "[%5s] ", "DEBUG");
            break;
        case CHECK_MODE:
            len += snprintf(buf+len, MODE_SIZE, "[%5s] ", "CHECK");
            break;
        case WARN_MODE:
            len += snprintf(buf+len, MODE_SIZE, "[%5s] ", "WARN");
            break;
        case ERROR_MODE:
            len += snprintf(buf+len, MODE_SIZE, "[%5s] ", "ERROR");
            break;
    }

    len += vsnprintf(buf+len, MSG_SIZE-1, format, arg);

    if (NULL != logger.log_file) {
        fwrite(buf, len, 1, logger.log_file);
    }

    if (mode >= logger.mode) {
        printf("%s", buf);
    }
}

Log_module *
log_module_new(Logger *logger, const u32 id, const char *name, const char *file)
{
    Log_module *module = logger->head;
    while (module) {
        if (0 == memcmp(module->name, name, sizeof(module->name))) {
            perror("Fail to create log module: already exist.\n");
            return NULL;
        }
        module = module->next;
    }

    module = (Log_module *) malloc(sizeof(Log_module));
    if (!module) {
        perror("Fail to malloc log_module: %s\n", name);
        return NULL;
    }
    memcpy(module, 0, sizeof(Log_module));

    module->id = id;
    memcpy(module->name, name, sizeof(module->name));
    memcpy(module->file, file, sizeof(module->file));
    module->fp = fopen(module->file, "w");

    return module;
}

/*
void INFO(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(__FILE__, __LINE__, INFO_MODE, format, arg);
}

void DEBUG(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(__FILE__, __LINE__, DEBUG_MODE, format, arg);
}

void CHECK(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(__FILE__, __LINE__, CHECK_MODE, format, arg);
}


void WARN(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(__FILE__, __LINE__, WARN_MODE, format, arg);
}

void ERROR(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _log(__FILE__, __LINE__, ERROR_MODE, format, arg);
}
*/
