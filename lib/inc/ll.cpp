/** @file ll.c
 *  @brief Contains encapsulated linked list implementation
 *
 *  @author Mukund Tibrewala (mukundt)
 *  @author Aishwarya Prem Renu (apremren)
 *  @bug No known bugs
 *
 */
#include <ll.h>
#include <stdlib.h>

/** @brief Initialize the linked list
 *
 *  @param ll Pointer to the linked list to be initialized
 *  @return Void.
 */
void ll_init(ll *l)
{
    l->head = NULL;
    l->tail = NULL;
}

/** @brief Return the data contained in a node
 *
 *  @param node Pointer to the node whose data is to be retreived
 *  @return Pointer to the data.
 */
void *ll_data(ll_node *node)
{
    return node->data;
}

/** @brief Enqueue a node given a pointer to it, the linked list and the
 *         and the data within it.
 *
 *  @param ll Pointer to the linked list
 *  @param node Pointer to the node to be enqueued
 *  @param data Pointer to the data to be a part of the node
 *  @return Void.
 */
void ll_enqueue(ll *l, ll_node *node, void *data)
{
    /* Initialize new node's data and predecessor/successor pointers */
    node->data = data;
    node->pred = NULL;
    node->succ = NULL;

    /* If list is empty, head and tail are both set to node */
    if (ll_empty(l)) {
        l->head = node;
        l->tail = node;
    }
    /* If list is non-empty, add node to tail */
    else {
        /* New node's predecessor is current tail */
        node->pred = l->tail;
        /* Current tail's successor is new node */
        l->tail->succ = node;
        /* Tail is set to new node */
        l->tail = node;
    }
}

/** @brief Dequeue a node given a pointer to the linked list
 *
 *  @param ll Pointer to the linked list
 *  @return Pointer to the dequeued node
 */
ll_node *ll_dequeue(ll *l)
{
    /* Store pointer to current head in old_head */
    ll_node *old_head = l->head;

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
void ll_delete(ll *l, ll_node *node)
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
ll_node *ll_head(ll *l)
{
    return l->head;
}

/** @brief Return the next node given a node
 *
 *  @param node Pointer to the node
 *  @return Pointer to the next node
 */
ll_node *ll_next(ll_node *node)
{
    return node->succ;
}

/** @brief Checks if the linked list is empty
 *
 *  @param ll Pointer to the linked list
 *  @return True if the linked list is empty and false
 *          otherwise.
 */
bool ll_empty(ll *l)
{
    return !l->head;
}