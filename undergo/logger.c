#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>


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

char g_log_buf[LOG_SIZE];

FILE* g_log_file = NULL;


int init_logger(char *log_file) {
    g_log_file = fopen(log_file, "ab");
    return 0;
}


void logger(const char *msg) {
    if (NULL == g_log_file) {
        return;
    }

    fwrite(msg, LOG_SIZE, 1, g_log_file);
}


void INFO(const char *format, ...) {

    va_list arg;
    va_start(arg, format);
    va_end(arg);
    vsnprintf(g_log_buf, LOG_SIZE, format, arg);
    logger(g_log_buf);

    if (info_mode < g_mode) {
        return;
    }

    printf("%s", g_log_buf);
}



int main () {
    g_mode = info_mode;
    INFO("123 %c %d %p\n", 'v', 87, NULL);
    
    const char *s = "12321";
    printf("%s\n", s);
}
