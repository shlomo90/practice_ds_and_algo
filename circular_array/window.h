#ifndef __WINDOW_H__
#define __WINDOW_H__

#define for_win_each(win, type, entry) \
    for (entry = (type)win->data; entry != ((type)win->data + win->size); (type)entry++)

#define for_win_from_start(win, type, entry)    \
    for (entry = win->pos == 0 ? ((type)win->data + (win->size - 1)) : ((type)win->data + win->pos -1);   \
            (type)entry++ != ((type)win->data + win->pos); \
            entry = (type)entry++ == ((type)win->data + win->size) ? (type)win->data : (type)(entry))

typedef unsigned int uint_t;
typedef struct win_s win_t;
typedef void (*cleanup_t) (win_t*);

struct win_s {
    uint_t       size;
    uint_t       pos;
    uint_t       unit;
    uint_t       rotated;
    void        *data;
    cleanup_t    cleanup;
};

void win_cleanup(win_t *win);
win_t*  win_init(uint_t win_size, uint_t unit);
void* win_push(win_t *win);
void* win_start(win_t *win);
void* win_last(win_t *win);
#endif
