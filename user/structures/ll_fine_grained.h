#ifndef LL_FINE_H
#define LL_FINE_H

#include <stdbool.h>
#include "../../lib/inc/mutex_type.h"

typedef struct ll_fine_node_str ll_fine_node;

/** Node struct for elements of the linked list */
struct ll_fine_node_str
{
    /** Pointer to data in the nodes of the linked list */
    void *data;
    /** Pointer to the previous node */
    ll_fine_node *succ;
    /** Mutex per node */
    mutex_t m;
};

/** Structure representing the linked list */
typedef struct
{
    /** Pointer to the first node of the linked list */
    ll_fine_node *head;
    /** Mutex to protect the linked list */
    mutex_t m;
    /** comparison function pointer */
    int (*compare)(void *adata, void *bdata);
} ll_fine;

void ll_fine_init(ll_fine *l, int (*compare)(ll_fine_node *a, ll_fine_node *b));

void ll_fine_insert(ll_fine *l, ll_fine_node *node, void *data);

void *ll_fine_data(ll_fine_node *node);

ll_fine_node *ll_fine_delete(ll_fine *l, void *data);

ll_fine_node *ll_fine_head(ll_fine *l);

ll_fine_node *ll_fine_next(ll_fine_node *node);

bool ll_fine_empty(ll_fine *l);

#endif /* LL_FINE_H */