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
void ll_fine_enqueue(ll_fine *l, ll_fine_node *node, void *data)
{
    /* Initialize new node's data and predecessor/successor pointers */
    node->data = data;
    node->succ = NULL;
    mutex_create(&(node->m));

    mutex_lock(&(node->m));

    /* If list is empty, head and tail are both set to node */
    if (ll_fine_empty(l)) {
        l->head = node;
        mutex_unlock(&(node->m));
    }
    /* If list is non-empty, add node to the right position */
    else {
        // head is locked right now
        ll_fine_node *pres = l->head;
        mutex_lock(&(pres->m));
        if (l->compare(node->data, pres->data) <= 0) {
            // means it has to be put in front of the first element
            node->succ = pres;
            l->head = node;
            mutex_unlock(&node->m));
            mutex_unlock(&(pres->m));
            return;
        }
        mutex_unlock(&node->m));
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

/** @brief Dequeue a node given a pointer to the linked list
 *
 *  @param ll Pointer to the linked list
 *  @return Pointer to the dequeued node
 */
ll_fine_node *ll_fine_dequeue(ll_fine *l)
{
    /* Store pointer to current head in old_head */
    ll_fine_node *old_head = l->head;

    /* If list has 0 or 1 node... */
    if (l->head == l->tail) {
        l->head = NULL;
        l->tail = NULL;
    /* Change current head to successor. We know that head has a successor
        because we entered this clause.
         */
    } else {
        l->head = l->head->succ;
        l->head->pred = NULL;
    }

    /* Will be null if list was empty! */
    return old_head;
}

/** @brief Delete a node from a linked list
 *
 *  @param ll Pointer to the linked list
 *  @param node Pointer to the node to be deleted
 *  @return Void.
 */
void ll_fine_delete(ll_fine *l, ll_fine_node *node)
{
    if (node == l->head) {
        ll_dequeue(l);
    }
    /* Note that if node is both head and tail, ll_dequeue() takes care of it.
        That's why this is 'else if' */
    else if (node == l->tail) {
        /* Tail is now null! */
        l->tail = l->tail->pred;
        /* Tail's successor is n=ow null! */
        l->tail->succ = NULL;
    } else {
        /* My predecessor's successor is set to my successor */
        node->pred->succ = node->succ;
        /* My successor's predecessor is set to my predecessor */
        node->succ->pred = node->pred;
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
