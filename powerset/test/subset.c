#include <stdio.h>
#include <string.h>

#include "common.h"
#include "subset.h"
#include "subset_list.h"
#include "subset_string.h"
#include "subset_node.h"


static int find_subsets(list_t *result, char* buf);
static void print_subsets(list_t *subset);
static int remove_duplicate(list_t *head);
static int _find_subset_recursive(list_t *result, list_t *running);

static int _find_subset_recursive(list_t *result, list_t *running)
{
    list_t      *entry, subset;
    int          ret;

    init_list(&subset);
    for_each_list(entry, running) {
        node_t      *node;

        node = list_entry(entry, node_t, running_queue);
        ret = get_substring_node(&subset, node);
        if (ret == DONE) {
            // Finished
            return OK;
        } else if (ret == ERROR) {
            return ERROR;
        }
    }

    remove_duplicate(&subset);
    
    // APPEND to result
    for_each_list(entry, &subset) {
        node_t      *node;

        node = list_entry(entry, node_t, running_queue);
        insert_list(result, &node->result_queue);
    }

    if (_find_subset_recursive(result, &subset) != OK) {
        return ERROR;
    }

    return OK;
}


static int remove_duplicate(list_t *head)
{
    list_t  *std_entry, *comp_entry;

    for_each_list(std_entry, head) {
        node_t  *std_node;
        string_t    *std_str;
        std_node = list_entry(std_entry, node_t, running_queue);
        std_str = std_node->data;

        for (comp_entry = std_entry->next; 
                comp_entry != head;
                comp_entry = comp_entry->next) {

            node_t      *comp_node;
            string_t    *comp_str;
            comp_node = list_entry(comp_entry, node_t, running_queue);
            comp_str = comp_node->data;

            if (std_str->len == comp_str->len &&
                    strncmp(std_str->value,
                            comp_str->value,
                            comp_str->len) == 0) {

                list_t      *temp;
                temp = comp_entry->prev;

                // Remove the duplicated node.
                remove_list(comp_entry);
                free_node(comp_node);
                comp_entry = temp;
            }
        }
    }

    return 0;
}


static int find_subsets(list_t *result, char* buf)
{
    /** find_subsets
     *
     * param:
     *    - character array.
     *
     * return:
     *    - subset's list (dynamic allocated)
     *    - NULL (if failed)
     */

    int          ret;
    node_t      *node;
    list_t       running;

    node = create_string_node(buf);
    if (node == NULL) {
        return ERROR;
    }

    init_list(result);
    init_list(&running);
    insert_list(&running, &node->running_queue);

    // Subset has itself.
    insert_list(result, &node->result_queue);

    ret = _find_subset_recursive(result, &running);
    if (ret != OK) {
        flush_result_node(result);
        return ERROR;
    }

    return OK;
}


static void print_subsets(list_t *subset)
{
    list_t *entry;

    printf("Result = { ");
    for_each_list(entry, subset) {
        node_t      *temp = list_entry(entry, node_t, result_queue);
        string_t    *str = temp->data;

        if (entry->prev != subset) {
            printf(", ");
        }

        if (str->len == 0) {
            printf("empty");
        } else {
            printf("%.*s", str->len, str->value);
        }
    }
    printf(" }\n");
}


int get_input_string_set(char* buf)
{
    int ret;

    printf("Input word: ");
    ret = scanf("%s", buf);

    if (ret == EOF || ret == 0) {
        return ERROR;
    }

    return OK;
}


int do_subset(void)
{
    int          ret;
    char         buf[MAX_BUF_SIZE] = {0,};
    list_t       result;

    string_t    *string_set; 
    node_t      *node;
    list_t       input_head, output_head, *entry, *temp;

    ret = get_input_string_set(buf);
    if (ret != OK) {
        return ERROR;
    }

    ret = find_subsets(&result, buf);
    if (ret != OK) {
        printf("Find subset Failed\n");
        return ERROR;
    }

    print_subsets(&result);
    return OK;
}
