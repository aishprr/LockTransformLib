/** @file ll.h
 *  @brief Contains prototypes for a doubly linked list implementation
 *
 *  @author Mukund Tibrewala (mukundt)
 *  @author Aishwarya Prem Renu (apremren)
 *  @bug No known bugs
 *
 */

#ifndef LL_H
#define LL_H

#include <stdbool.h>

typedef struct ll_node_str ll_node;

/** Node struct for elements of the linked list */
struct ll_node_str
{
    /** Pointer to data in the nodes of the linked list */
    void *data;
    /** Pointer to the previous node */
    ll_node *pred;
    /** Pointer to the successor node */
    ll_node *succ;
};

/** Structure representing the linked list */
typedef struct
{
    /** Pointer to the first node of the linked list */
    ll_node *head;
    /** Pointer to the last node of the linked list */
    ll_node *tail;
} ll;

void ll_init(ll *l);

void ll_enqueue(ll *l, ll_node *node, void *data);

void *ll_data(ll_node *node);

ll_node *ll_dequeue(ll *l);

void ll_delete(ll *l, ll_node *node);

ll_node *ll_head(ll *l);

ll_node *ll_next(ll_node *node);

bool ll_empty(ll *l);

#endif /* LL_H */