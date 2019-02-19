/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    /* How about freeing the list elements and the strings? */
    while (q_size(q) > 0)
        q_remove_head(q, NULL, 0);
    /* Free queue structure */
    free(q);
}

/*
  Attempt to allocate an new element.
  Return pointer to new element if successful.
  Return NULL if could not allocate space.
  Allocate space and copy the string into it.
 */
static list_ele_t *q_allocate_new(char *s)
{
    list_ele_t *newh;
    char *data = NULL;
    size_t len;

    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    if (s) {
        len = strlen(s) + 1;
        data = (char *) malloc(len);
        if (data == NULL) {
            free(newh);
            return NULL;
        }
        memcpy(data, s, len);
    }

    newh->value = data;
    newh->next = NULL;

    return newh;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    if (q == NULL)
        return false;

    newh = q_allocate_new(s);
    if (newh == NULL)
        return false;

    newh->next = q->head;
    q->head = newh;
    q->size += 1;

    if (!q->tail)
        q->tail = newh;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;

    if (q == NULL)
        return false;

    newh = q_allocate_new(s);
    if (newh == NULL)
        return false;

    if (q->tail)
        q->tail->next = newh;
    q->tail = newh;
    q->size += 1;

    if (!q->head)
        q->head = newh;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    size_t len;
    list_ele_t *head;

    if (q == NULL)
        return false;

    if (q->head == NULL)
        return false;
    head = q->head;

    if (head->value) {
        if (sp && head->value) {
            len = strlen(head->value);
            len = (len > bufsize - 1) ? bufsize - 1 : len;
            memcpy(sp, head->value, len);
            sp[len] = '\0';
        }
        free(head->value);
        head->value = NULL;
    }

    q->head = q->head->next;
    q->size -= 1;
    free(head);

    if (q->head == NULL)
        q->tail = NULL;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;

    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
}
