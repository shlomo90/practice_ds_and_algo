#include <stdio.h>

#include "window.h"


typedef struct data_s data_t;

struct data_s {
    int id;
    int good;
    int bad;
};


int main(int argc, char* argv)
{
    int      i = 0;
    uint_t   s = 10;
    win_t   *w = NULL;
    data_t  *d = NULL;

    w = win_init(s, sizeof(data_t));
    if (w == NULL) {
        return 1;
    }

    s += 5;
    for (i = 0; i < s; i++) {
        d = (data_t*)win_push(w);
        d->id = i + 1;
        d->good = i * 9 + (s - i) * 2;
        d->bad = s - i;
    }

    for (i = 0; i < s; i++) {
        d = (data_t*)win_push(w);
        d->id = i + 1;
        d->good = i * 9 + (s - i) * 2;
        d->bad = s - i;
    }

    //for_win_each(w, data_t*, d) {
    for_win_from_start(w, data_t*, d) {
        printf("D: id:%d, good: %d, bad: %d\n", d->id, d->good, d->bad);
    }

    return 0;
}
