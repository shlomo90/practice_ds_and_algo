#include <stdlib.h>
#include <string.h>

#include "window.h"

void win_cleanup(win_t *win)
{
    free(win->data);
    free(win);
}

win_t*  win_init(uint_t win_size, uint_t unit)
{
    win_t   *win;

    win = malloc(sizeof(win_t));
    if (win == NULL) {
        return NULL;
    }

    win->data = malloc(unit * win_size);
    if (win->data == NULL) {
        goto win_data_fail;
    }
    memset(win->data, 0, unit * win_size);

    win->pos = 0;
    win->unit = unit;
    win->size = win_size;
    win->cleanup = win_cleanup;
    return win;

win_data_fail:
    free(win);
    return NULL;
}

void* win_push(win_t *win)
{
    uint_t   last;
    unsigned char   *d;

    last = win->pos;
    d = win->data + (win->unit * win->pos);

    win->pos = ++win->pos % win->size;
    if (win->pos == 0) {
        win->rotated = 1;
    }

    return (void*)d;
}

void* win_start(win_t *win)
{
    if (win->rotated) {
        return win->data;
    } else {
        return win->data + (win->unit * win->pos);
    }
}

void* win_last(win_t *win)
{
    if (win->pos == 0) {
        return (void*)(win->data + (win->unit * win->size));
    } else {
        return (void*)(win->data + (win->unit * (win->pos - 1)));
    }
}
