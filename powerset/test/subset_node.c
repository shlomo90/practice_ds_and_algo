#include <stdlib.h>

#include "common.h"
#include "subset_list.h"
#include "subset_string.h"

// function declare and define structure
#include "subset_node.h"


void flush_running_node(list_t *head)
{
    list_t  *entry, *prev;

    for_each_list(entry, head) {
        node_t  *node;

        prev = entry->prev;
        node = list_entry(entry, node_t, running_queue);
        remove_list(entry);
        free_node(node);
        entry = prev;
    }
}


void flush_result_node(list_t *head)
{
    list_t  *entry, *prev;

    for_each_list(entry, head) {
        node_t  *node;

        prev = entry->prev;
        node = list_entry(entry, node_t, result_queue);
        remove_list(entry);
        free_node(node);
        entry = prev;
    }
}

node_t* create_string_node(char* buf)
{
    string_t    *str;
    node_t      *new;

    str = create_string(buf);
    if (str == NULL) {
        return NULL;
    }

    new = (node_t*)malloc(sizeof(node_t));
    if (new == NULL) {
        goto fail_node;
    }

    init_list(&new->running_queue);
    init_list(&new->result_queue);
    new->data = str;
    return new;

fail_node:
    free_string(str);
    return NULL;

}


void free_node(node_t *target)
{
    free_string(target->data);
    free(target);
}


int get_substring_node(list_t* head, node_t* node)
{
    unsigned int     i, len;
    char             c;
    string_t        *string;
    list_t          *entry;

    string = (string_t*)node->data;
    len = string->len;

    // CHECK is empty set
    if (len == 0) {
        return DONE;
    }

    // MAKE Substring Nodes
    for (i = 0; i < len; i++) {
        node_t          *new;
        unsigned int     j, index = 0;
        char             substring[MAX_BUF_SIZE] = {0,};

        for (j = 0; j < len; j++) {
            if (j == i) {
                continue;
            }
            substring[index++] = string->value[j];
        }

        new = create_string_node(substring);
        if (new == NULL) {
            flush_running_node(head);
            return ERROR;
        }

        insert_list(head, &new->running_queue);
    }

    return 0;
}
