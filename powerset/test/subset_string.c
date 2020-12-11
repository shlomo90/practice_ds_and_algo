#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "subset_string.h"


string_t* create_string(char* buf)
{
    string_t        *new;
    unsigned int     len;
    char            *str;

    len = strlen(buf);
    str = malloc(sizeof(char) * len);
    if (str == NULL) {
        return NULL;
    }

    memcpy(str, buf, len);

    new = malloc(sizeof(string_t));
    if (new == NULL) {
        goto fail_string;
    }

    new->len = len;
    new->value = str;
    return new;

fail_string:
    free(str);
    return NULL;
}


void free_string(string_t *string)
{
    free(string->value);
    free(string);
}
