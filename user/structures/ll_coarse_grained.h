#ifndef LL_COARSE_H
#define LL_COARSE_H

#include <stdbool.h>
#include "../../lib/inc/mutex_type.h"

typedef struct ll_coarse_node_str ll_coarse_node;

/** Node struct for elements of the linked list */
struct ll_coarse_node_str
{
    /** Pointer to data in the nodes of the linked list */
    void *data;
    /** Pointer to the previous node */
    ll_coarse_node *succ;
};

/** Structure representing the linked list */
typedef struct
{
    /** Pointer to the first node of the linked list */
    ll_coarse_node *head;
    /** Mutex to protect the linked list */
    mutex_t m;
    /** comparison function pointer */
    int (*compare)(void *adata, void *bdata);
} ll_coarse;

void ll_coarse_init(ll_coarse *l, int (*compare)(void *a, void *b));

void ll_coarse_insert(ll_coarse *l, ll_coarse_node *node, void *data);

void *ll_coarse_data(ll_coarse_node *node);

int ll_coarse_count_elems(ll_coarse *l);

ll_coarse_node *ll_coarse_delete(ll_coarse *l, void *data);

ll_coarse_node *ll_coarse_head(ll_coarse *l);

ll_coarse_node *ll_coarse_next(ll_coarse_node *node);

bool ll_coarse_empty(ll_coarse *l);

#endif /* LL_COARSE_H */