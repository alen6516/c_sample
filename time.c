#include <time.h>

static clock_t _START_CLOCK, _END_CLOCK;
static double _DURATION;

void start_clock() {
    _START_CLOCK = clock();
}

void stop_clock() {
    _END_CLOCK = clock();
    _DURATION = (double)(_END_CLOCK - _START_CLOCK)/CLOCKS_PER_SEC;
}

double get_duration() {
    return _DURATION;
}
