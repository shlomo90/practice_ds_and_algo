#ifndef __SUBSET_STRING_H__
#define __SUBSET_STRING_H__

typedef struct string_s string_t;

struct string_s {
    unsigned int   len;
    char          *value;
};


string_t* create_string(char *buf);
void free_string(string_t *string);
#endif
