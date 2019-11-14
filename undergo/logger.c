#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>


#define LOG_SIZE 100


enum mode_e {
    debug_mode = 0,
    info_mode,
    check_mode,
    warn_mode,
    error_mode
};


/* now mode is */
unsigned char g_mode = check_mode;


/* convert int of base 2, 10, 16 to str */
static char* __convert(unsigned int num, int base) {
    static const char REP[] = "0123456789ABCDEF";
    static char buff[LOG_SIZE];
    char *p;
    p = &buff[LOG_SIZE-1];
    *p = '\0';

    do {
        *(--p) = REP[num % base];
        num /= base;
    } while (num != 0);

    return p;
}


void logger(const char *format, ...) {
    const char *traverse;
    unsigned long _lu;
    long _ld;
    char *_s;
    int base = 0;

    char buff[LOG_SIZE];
    int j = 0;

    va_list arg;
    va_start(arg, format);

    traverse = format;
    while (*traverse != '\0' && j < LOG_SIZE-1) {
        
        while (*traverse != '%') {
            buff[j] = *traverse;
            j++, traverse++;

            if (j == LOG_SIZE-1) {
                goto finish;
            }
        }

        traverse ++;
        switch (*traverse) {
        
            case 'c':
                _ld = va_arg(arg, int);
                buff[j] = _ld;
                j++;
                if (j == LOG_SIZE-1) {
                    goto finish;
                }
                break;

            case 'd':
            case 'i':
                base = 10;
                _ld = va_arg(arg, int);
                if (_ld < 0) {
                    _ld = -_ld;
                    buff[j] = '-';
                    j++;
                    if (j == LOG_SIZE-1) {
                        goto finish;
                    }
                }
                _s = __convert(_ld, base);
                for (int k=0; _s[k] != '\0'; k++) {
                    buff[j] = _s[k];
                    j++;
                    if (j == LOG_SIZE-1) {
                        goto finish;
                    }
                }
                break;

            case 'u':
                if (base == 0) { base = 10; }
            case 'x':
                if (base == 0) { base = 16; }
            case 'o':
                if (base == 0) { base = 8; }
                
                _lu = va_arg(arg, unsigned int);

                _s = __convert(_lu, base);
                for (int k=0; _s[k] != '\0'; k++) {
                    buff[j] = _s[k];
                    j++;
                    if (j == LOG_SIZE-1) {
                        goto finish;
                    }
                }
                break;

            case 's':
                _s = va_arg(arg, char *);
                for (int k=0; _s[k] != '\0'; k++) {
                    buff[j] = _s[k];
                    j++;
                    if (j == LOG_SIZE-1) {
                        goto finish;
                    }
                }
                break;
            case 'p':
                _lu = va_arg(arg, unsigned long);

                buff[j] = '0';
                j ++;
                buff[j] = 'x';
                j ++;

                _s = __convert(_lu, 16);
                for (int k=0; _s[k] != '\0'; k++) {
                    buff[j] = _s[k];
                    j++;
                    if (j == LOG_SIZE-1) {
                        goto finish;
                    }
                }
                break;
        }
        traverse ++;
    }

    va_end(arg);

finish:
    printf("%s\n", buff);
    return ;
}


int main () {

    logger("123%c%c%c num is %u, str is %s\n", 'a', 'b', 'c', -1, "12312");
    printf("%u\n", -1);
    
}

#endif
