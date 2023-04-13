#include "defs.h"

/**
 * @brief Initializes deque, allocates memory, assigns head and tail pointers to NULL
 * 
 * @param d in-out: unitialized deque
 */
void initDeque(DequeType **d) {
    *d = malloc(sizeof(DequeType));
    (*d)->head = NULL;
    (*d)->tail = NULL;
}

/**
 * @brief adds a fighter to the back of the deque
 * 
 * @param d in-out: deque to add too
 * @param f in: fighter to add
 */
void addToDeque(DequeType *d, FighterType *f) {
    NodeType *n;
    n = malloc(sizeof(NodeType));
    n->data = f;
    n->next = NULL;
    if (d->head == NULL) {
        d->head = n;
        d->tail = d->head;
    } else {
        d->tail->next = n;
        d->tail = n;
    }
}

/**
 * @brief removes a fighter from the front of the deque
 * NOTE: will segfault if deque is empty, program flow always checks for this beforehand with hasNext, is intended behaviour
 * 
 * @param d in: deque to remove fighter from
 * @return out: FighterType* head of deque 
 */
FighterType *popFront(DequeType *d) {
    FighterType *f = d->head->data;
    NodeType *next = d->head->next;

    free(d->head);
    d->head = next;
    if (next == NULL) {  //only one pirate in deque (which we just popped)
        d->tail = NULL;
    }
    return f;
}
/**
 * @brief removes a fighter from the back of the deque
 * NOTE: will segfault if deque is empty, program flow always checks for this beforehand with hasNext, is intended behaviour
 * 
 * @param d in: deque to remove fighter from
 * @return out: FighterType* tail of deque 
 */
FighterType *popBack(DequeType *d) {
    FighterType *f = d->tail->data;
    NodeType *current = d->head;

    if (d->head->next == NULL) {
        free(d->tail);
        d->head = NULL;
        d->tail = NULL;
    } else {
        while (current->next != d->tail) {
            current = current->next;
        }
        free(d->tail);
        current->next = NULL;
        d->tail = current;
    }
    return f;
}

/**
 * @brief Checks if deque has Nodes to process
 * 
 * @param d in: deque 
 * @return out: int 0 if empty and 1 if Nodes 
 */
int hasNext(DequeType *d) {
    return (d->head == NULL) ? 0 : 1;
}

/**
 * @brief Copies data from source deque to destination by duplicating all data (ie pointers are not shared)
 * 
 * @param src   in: source deque to copy
 * @param dest  in-out: destination deque to populate with duplicated data
 */
void deepCopy(DequeType *src, DequeType *dest) {
    NodeType *current = src->head;
    FighterType *f;
    while (current != NULL) {
        initFighter(current->data->strength, current->data->armour, current->data->health, &f);
        addToDeque(dest, f);
        current = current->next;
    }
}

/**
 * @brief Deallocates dynamically allocated memory for all remaining nodes and fighters in deque and for deque itself
 * 
 * @param d in-out: deque
 */
void cleanupDeque(DequeType *d) {
    NodeType *current = d->head;
    NodeType *next;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(d);
}