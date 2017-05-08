/** @file ll.c
 *  @brief Contains encapsulated linked list implementation
 *
 *  @author Mukund Tibrewala (mukundt)
 *  @author Aishwarya Prem Renu (apremren)
 *  @bug No known bugs
 *
 */
#include "ll_fine_grained.h"
#include "../../lib/inc/mutex_type.h"
#include <stdlib.h>

/** @brief Initialize the linked list
 *
 *  @param ll Pointer to the linked list to be initialized
 *  @return Void.
 */
void ll_fine_init(ll_fine *l, int (*compare)(void *adata, void *bdata))
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
void *ll_fine_data(ll_fine_node *node)
{
    mutex_lock(&(node->m));
    void *data = node->data;
    mutex_unlock(&(node->m));
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
void ll_fine_insert(ll_fine *l, ll_fine_node *node, void *data)
{
    /* Initialize new node's data and predecessor/successor pointers */
    node->data = data;
    node->succ = NULL;
    mutex_create(&(node->m));

    mutex_lock(&(l->m));

    /* If list is empty, head and tail are both set to node */
    if (ll_fine_empty(l)) {
        l->head = node;
        mutex_unlock(&(l->m));
    }
    /* If list is non-empty, add node to the right position */
    else {
        // l is locked right now
        ll_fine_node *pres = ll_fine_head(l);
        mutex_lock(&(pres->m));
        if (l->compare(node->data, pres->data) <= 0) {
            // means it has to be put in front of the first element
            node->succ = pres;
            l->head = node;
            mutex_unlock(&(l->m));
            mutex_unlock(&(pres->m));
            return;
        }
        mutex_unlock(&(l->m));
        while(ll_fine_next(pres)) {
            // pres lock is held right now
            ll_fine_node *next = pres->succ;
            // pres and next locks are held right now
            mutex_lock(&(next->m));
            if (l->compare(node->data, next->data) <= 0) {
                node->succ = next;
                pres->succ = node;
                mutex_unlock(&(pres->m));
                mutex_unlock(&(next->m));
                return;
            }
            mutex_unlock(&(pres->m));
            pres = next;
        }

        // we didn't find it until the end
        // the only thing locked is now the last node
        // the only lock still held is the last node
        pres->succ = node;
        node->succ = NULL;
        mutex_unlock(&(pres->m));
    }
}

/** @brief Delete a node from a linked list
 *
 *  @param ll Pointer to the linked list
 *  @param node Pointer to the node to be deleted
 *  @return Void.
 */
ll_fine_node *ll_fine_delete(ll_fine *l, void *data)
{
    ll_fine_node *del;
    mutex_lock(&(l->m));
    /* If list is empty, head and tail are both set to node */
    if (ll_fine_empty(l)) {
        del = NULL;
        mutex_unlock(&(l->m));
        return del;
    }
    /* If list is non-empty, delete the right node */
    else {
        // l is locked right now
        ll_fine_node *pres = ll_fine_head(l);
        mutex_lock(&(pres->m));
        if (l->compare(data, pres->data) == 0) {
            // means it has to be put in front of the first element
            del = pres;
            l->head = NULL;
            mutex_unlock(&(l->m));
            mutex_unlock(&(pres->m));
            return del;
        }
        mutex_unlock(&(l->m));
        while(ll_fine_next(pres)) {
            // pres lock is held right now
            ll_fine_node *next = pres->succ;
            // pres and next locks are held right now
            mutex_lock(&(next->m));
            if (l->compare(data, next->data) == 0) {
                del = next;
                pres->succ = next->succ;
                mutex_unlock(&(pres->m));
                mutex_unlock(&(next->m));
                return del;
            }
            mutex_unlock(&(pres->m));
            pres = next;
        }

        // we didn't find it until the end
        // the only thing locked is now the last node
        // the only lock still held is the last node
        mutex_unlock(&(pres->m));
        return NULL;
    }
}

/** @brief Return the head of the linked list
 *
 *  @param ll Pointer to the linked list
 *  @return Pointer to the head node
 */
 // hold locks outside
ll_fine_node *ll_fine_head(ll_fine *l)
{
    return l->head;
}

/** @brief Return the next node given a node
 *
 *  @param node Pointer to the node
 *  @return Pointer to the next node
 */
 // hold locks outside
ll_fine_node *ll_fine_next(ll_fine_node *node)
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
bool ll_fine_empty(ll_fine *l)
{
    return !l->head;
}
