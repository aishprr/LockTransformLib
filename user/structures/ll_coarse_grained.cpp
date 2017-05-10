
#include "ll_coarse_grained.h"
#include "../../lib/inc/mutex_type.h"
#include <stdlib.h>

/** @brief Initialize the linked list
 *
 *  @param ll Pointer to the linked list to be initialized
 *  @return Void.
 */
void ll_coarse_init(ll_coarse *l, int (*compare)(void *adata, void *bdata))
{
    l->compare = compare;
    mutex_create(&(l->m));
    l->head = NULL;
}

/** @brief Return the data contained in a node
 *
 *  @param node Pointer to the node whose data is to be retreived
 *  @return Pointer to the data.
 */
void *ll_coarse_data(ll_coarse_node *node)
{
    void *data = node->data;
    return data;
}

/** @brief Enqueue a node given a pointer to it, the linked list and the
 *         and the data within it.
 *
 *  @param ll Pointer to the linked list
 *  @param node Pointer to the node to be enqueued
 *  @param data Pointer to the data to be a part of the node
 *  @return Void.
 */
void ll_coarse_insert(ll_coarse *l, ll_coarse_node *node, void *data)
{
    /* Initialize new node's data and predecessor/successor pointers */
    node->data = data;
    node->succ = NULL;
    
    mutex_lock(&(l->m));

    /* If list is empty, head and tail are both set to node */
    if (ll_coarse_empty(l)) {
        l->head = node;
        mutex_unlock(&(l->m));
    }
    /* If list is non-empty, add node to the right position */
    else {
        // l is locked right now
        ll_coarse_node *pres = ll_coarse_head(l);
        if (l->compare(node->data, pres->data) <= 0) {
            // means it has to be put in front of the first element
            node->succ = pres;
            l->head = node;
            mutex_unlock(&(l->m));
            return;
        }
        while(ll_coarse_next(pres)) {
            // pres lock is held right now
            ll_coarse_node *next = pres->succ;
            // pres and next locks are held right now
            if (l->compare(node->data, next->data) <= 0) {
                node->succ = next;
                pres->succ = node;
                mutex_unlock(&(l->m));
                return;
            }
            pres = next;
        }

        // we didn't find it until the end
        // the only thing locked is now the last node
        // the only lock still held is the last node
        pres->succ = node;
        node->succ = NULL;
        mutex_unlock(&(l->m));
    }
}

/** @brief Delete a node from a linked list
 *
 *  @param ll Pointer to the linked list
 *  @param node Pointer to the node to be deleted
 *  @return Void.
 */
ll_coarse_node *ll_coarse_delete(ll_coarse *l, void *data)
{
    ll_coarse_node *del;
    mutex_lock(&(l->m));
    /* If list is empty, head and tail are both set to node */
    if (ll_coarse_empty(l)) {
        del = NULL;
        mutex_unlock(&(l->m));
        return del;
    }
    /* If list is non-empty, delete the right node */
    else {
        // l is locked right now
        ll_coarse_node *pres = ll_coarse_head(l);
        if (l->compare(data, pres->data) == 0) {
            // means it has to be put in front of the first element
            del = pres;
            l->head = NULL;
            mutex_unlock(&(l->m));
            return del;
        }
        while(ll_coarse_next(pres)) {
            // pres lock is held right now
            ll_coarse_node *next = pres->succ;
            // pres and next locks are held right now
            if (l->compare(data, next->data) == 0) {
                del = next;
                pres->succ = next->succ;
                mutex_unlock(&(l->m));
                return del;
            }
            pres = next;
        }

        // we didn't find it until the end
        // the only thing locked is now the last node
        // the only lock still held is the last node
        mutex_unlock(&(l->m));
        return NULL;
    }
}

/** NOT THREAD SAFE -- just for checking purposes */
int ll_coarse_count_elems(ll_coarse *l) {
    if (ll_coarse_empty(l)) {
        return 0;
    } else {
        ll_coarse_node *pres = l->head;
        int num = 1;
        while(ll_coarse_next(pres)) {
            // pres lock is held right now
            ll_coarse_node *next = pres->succ;
            pres = next;
            // pres and next locks are held righ  
            num++;  
        }
        return num;
    }
    
}

/** @brief Return the head of the linked list
 *
 *  @param ll Pointer to the linked list
 *  @return Pointer to the head node
 */
 // hold locks outside
ll_coarse_node *ll_coarse_head(ll_coarse *l)
{
    return l->head;
}

/** @brief Return the next node given a node
 *
 *  @param node Pointer to the node
 *  @return Pointer to the next node
 */
 // hold locks outside
ll_coarse_node *ll_coarse_next(ll_coarse_node *node)
{
    return node->succ;
}

/** @brief Checks if the linked list is empty
 *
 *  @param ll Pointer to the linked list
 *  @return True if the linked list is empty and false
 *          otherwise.
 */
 // Hold locks outside
bool ll_coarse_empty(ll_coarse *l)
{
    return !l->head;
}
