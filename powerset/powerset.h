#include "common.h"

typedef struct set_s set_t;

struct set_s {
    int              idx_last;
    int              bit_last;
    int              len;
    char            *str;
    unsigned char    bits[64];
    int            (*count_handler)(set_t*);
    void           (*print_handler)(set_t*);
};


int do_powerset(void);
