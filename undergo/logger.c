#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>


#define PRE_SIZE 8
#define LOG_SIZE 100


enum mode_e {
    info_mode = 0,
    debug_mode,
    check_mode,
    warn_mode,
    error_mode
};


/* now mode is */
unsigned char g_mode = check_mode;

FILE* g_log_file = NULL;

int init_logger(char *log_file) {
    g_log_file = fopen(log_file, "ab");
    return 0;
}


static inline void logger(int mode, const char *format, va_list arg) {
    char buf[PRE_SIZE+LOG_SIZE];

    switch (mode) {
        case info_mode:
            snprintf(buf, PRE_SIZE+LOG_SIZE, "[%5s] %s", "INFO", format);
            break;
        case debug_mode:
            snprintf(buf, PRE_SIZE+LOG_SIZE, "[%5s] %s", "DEBUG", format);
            break;
        case check_mode:
            snprintf(buf, PRE_SIZE+LOG_SIZE, "[%5s] %s", "CHECK", format);
            break;
        case warn_mode:
            snprintf(buf, PRE_SIZE+LOG_SIZE, "[%5s] %s", "DEBUG", format);
            break;
        case error_mode:
            snprintf(buf, PRE_SIZE+LOG_SIZE, "[%5s] %s", "DEBUG", format);
            break;
    }

    vsnprintf(buf + PRE_SIZE, LOG_SIZE, format, arg);

    if (NULL != g_log_file) {
        fwrite(buf, PRE_SIZE+LOG_SIZE, 1, g_log_file);
    }

    if (mode >= g_mode) {
        printf("%s", buf);
    }
}


void INFO(const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);
    logger(info_mode, format, arg);
}

void DEBUG(const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);
    logger(debug_mode, format, arg);
}

void CHECK(const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);
    logger(check_mode, format, arg);
}


void WARN(const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);
    logger(warn_mode, format, arg);
}

void ERROR(const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);
    logger(error_mode, format, arg);
}

int main () {
    g_mode = info_mode;
    INFO("123 %c %d %p\n", 'v', 87, NULL);
    
    const char *s = "12321";
    printf("%s\n", s);
}
