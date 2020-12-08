#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "powerset.h"




char* input_string(void)
{
    char     buf[MAX_BUF_SIZE] = {0,};
    char    *new;
    int      ret, len;

    printf("Input word: ");
    ret = scanf("%s", buf);

    if (ret == EOF || ret == 0) {
        return NULL;
    }

    len = strnlen(buf, MAX_BUF_SIZE);
    new = malloc(sizeof(char) * len);
    if (new == NULL) {
        return NULL;
    }
    memcpy(new, buf, len);
    new[len] = '\0';
    return new;
}


int count_bits(set_t *target)
{
    int i;

    target->print_handler(target);

    // COUNT bit
    for(i = 0; i < 64; i++) {
        if (i == target->idx_last && target->bits[i] == target->bit_last) {
            // Over
            return ERROR;
        }
        if (target->bits[i] == 0xff) {
            target->bits[i] = 0;
        } else {
            target->bits[i]++;
            break;
        }
    }
    return OK;
}

void print_bits(set_t *target)
{
    int i;
    unsigned char   c;
    int bit_set = 0;

    for (i = 0; i <= target->idx_last; i++) {
        c = target->bits[i];
        if (c & 0x01) {
            bit_set = 1;
            printf("%c", target->str[i*8]);
        }
        if (c & 0x02) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 1]);
        }
        if (c & 0x04) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 2]);
        }
        if (c & 0x08) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 3]);
        }
        if (c & 0x10) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 4]);
        }
        if (c & 0x20) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 5]);
        }
        if (c & 0x40) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 6]);
        }
        if (c & 0x80) {
            bit_set = 1;
            printf("%c", target->str[i*8 + 7]);
        }
    }

    if (bit_set == 0) {
        printf("empty");
    }
    printf("\n");
}


set_t* bit_set(char* buf)
{
    int     bit_shift = 0;
    unsigned char   bit;
    set_t   *set;

    set = malloc(sizeof(set_t));
    if (set == NULL) {
        return NULL;
    }
    memset(set, 0, sizeof(set_t));

    set->len = strlen(buf);

    bit_shift = set->len % 8;
    bit = 0xff;
    bit = bit << bit_shift;
    bit = ~bit;
    set->bit_last = bit;

    set->idx_last = (set->len / (8+1));

    set->str = buf;
    set->count_handler = count_bits;
    set->print_handler = print_bits;
    return set;
}


int do_powerset(void)
{
    int     ret;
    char    *buf;
    set_t   *set;

    buf = input_string();
    if (buf == NULL) {
        return ERROR;
    }

    set = bit_set(buf);
    if (set == NULL) {
        free(buf);
        return ERROR;
    }

    // print
    for (ret = set->count_handler(set); ret == OK; ret = set->count_handler(set));
}
