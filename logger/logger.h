#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

<<<<<<< HEAD

#define LOGGER_FILE "./log.txt"
#define PRE_SIZE 9      // "[WARN] "
#define LOG_SIZE 100    // msg body 
=======
#define LOGGER_FILE "./log.txt"
#define FILE_LINE_SIZE 40 // this_is_file_name: 900
#define MODE_SIZE 10       // "[WARN] "
#define MSG_SIZE 100      // msg body 
>>>>>>> 80a804ea05c0499ce9a8e0e49aaab8ea54f1471c


typedef enum {
    INFO_MODE = 0,
    DEBUG_MODE,
    CHECK_MODE,
    WARN_MODE,
    ERROR_MODE
} mode_e;


<<<<<<< HEAD
struct logger_t {
    mode_e mode;
    FILE* log_file;
};

#define LOGGER_CALLOC() (struct logger_t*)calloc(1, sizeof(struct logger_t))


int init_logger(const char *);

void _log(mode_e this_mode, const char *format, va_list arg);


void INFO(const char *format, ...);
void DEBUG(const char *format, ...);
void CHECK(const char *format, ...);
void WARN(const char *format, ...);
void ERROR(const char *format, ...);
=======
typedef struct __logger {
    mode_e mode;
    FILE* log_file;
    unsigned char file_line_f :1,
                  spare:       7;
} logger_t;

#define LOGGER_CALLOC() (logger_t*)calloc(1, sizeof(logger_t))

extern logger_t logger;

int init_logger(const char*);

void _log(const char*, unsigned long, mode_e, const char *, va_list);


//void INFO(const char *format, ...);
//void DEBUG(const char *format, ...);
//void CHECK(const char *format, ...);
//void WARN(const char *format, ...);
//void ERROR(const char *format, ...);

#define INFO(format, ...)  _log(__FILE__, __LINE__, INFO_MODE, format, __VA_ARGS__)
#define DEBUG(format, ...) _log(__FILE__, __LINE__, DEBUG_MODE, format, __VA_ARGS__)
#define CHECK(format, ...) _log(__FILE__, __LINE__, CHECK_MODE, format, __VA_ARGS__)
#define WARN(format, ...)  _log(__FILE__, __LINE__, WARN_MODE, format, __VA_ARGS__)
#define ERROR(format, ...) _log(__FILE__, __LINE__, ERROR_MODE, format, __VA_ARGS__)
>>>>>>> 80a804ea05c0499ce9a8e0e49aaab8ea54f1471c


/*
int main () {
    g_mode = info_mode;
    INFO("123 %c %d %p\n", 'v', 87, NULL);
    
    const char *s = "12321";
    printf("%s\n", s);
}
*/
#endif
