#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#define LOGGER_FILE "./log.txt"
#define FILE_LINE_SIZE 40 // this_is_file_name: 900
#define MODE_SIZE 10       // "[WARN] "
#define MSG_SIZE 100      // msg body 


typedef enum {
    INFO_MODE = 0,
    DEBUG_MODE,
    CHECK_MODE,
    WARN_MODE,
    ERROR_MODE
} LOG_MODE;

typedef struct __log_module {
    u32  id;
    char name[10];
    char file[10]
    FILE *fp;
    LOG_MODE mode;
    struct __log_module *next;
} Log_module

typedef struct __logger {
    LOG_MODE mode;
    char file[10];
    FILE* fp;
    unsigned char is_file_line_on :1,
                  spare:       7;
    Log_module *head_module;
} Logger;


extern LOGGER logger;

int init_logger(LOGGER *logger, const char* file);
void _log(const char*, unsigned long, LOG_MODE, const char *, ...);

#define DEBUG(format, ...) _log(__FILE__, __LINE__, DEBUG_MODE, format, ##__VA_ARGS__)
#define INFO(format, ...)  _log(__FILE__, __LINE__, INFO_MODE, format, ##__VA_ARGS__)
#define WARN(format, ...)  _log(__FILE__, __LINE__, WARN_MODE, format, ##__VA_ARGS__)
#define ERROR(format, ...) _log(__FILE__, __LINE__, ERROR_MODE, format, ##__VA_ARGS__)

/*
int main () {
    g_mode = info_mode;
    INFO("123 %c %d %p\n", 'v', 87, NULL);
    
    const char *s = "12321";
    printf("%s\n", s);
}
*/
#endif
