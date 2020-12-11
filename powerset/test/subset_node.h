#ifndef __SUBSET_NODE_H__
#define __SUBSET_NODE_H__

#include "subset_list.h"

typedef struct node_s   node_t;

struct node_s {
    list_t       running_queue;
    list_t       result_queue;
    void        *data;
};


void flush_running_node(list_t *head);
void flush_result_node(list_t *head);
node_t* create_string_node(char* buf);
void free_node(node_t *target);
int get_substring_node(list_t* head, node_t* node);
#endif
