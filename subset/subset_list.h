
#ifndef __SUBSET_LIST_H__
#define __SUBSET_LIST_H__
#include <stddef.h>

typedef struct list_s list_t;

struct list_s {
    struct list_s *prev;
    struct list_s *next;
};

#define container_of(ptr, type, member) ({	\
		const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
		(type *)( (char *)__mptr - offsetof(type,member) );})

// linked list init
#define init_list(node)     \
    (node)->prev = node;    \
    (node)->next = node;

// linked list insert.
#define insert_list(target, node)       \
    (node)->prev = (target);            \
    (node)->next = (node)->prev->next;  \
    (target)->next->prev = (node);      \
    (target)->next = (node);

#define remove_list(node)               \
    (node)->prev->next = (node)->next;  \
    (node)->next->prev = (node)->prev;  \
    (node)->next = NULL;                \
    (node)->prev = NULL;

#define for_each_range(entry, start, end)   \
    for ((entry) = (start); (entry) != (end); (entry) = (entry)->next)

#define for_each_list(entry, head)     \
    for ((entry) = (head)->next; (entry) != (head); (entry) = (entry)->next)

#define list_entry(ptr, type, member)   \
    container_of(ptr, type, member)


#endif
