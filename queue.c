#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

static void *emalloc(size_t size)
{
    void *p;
    
    p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "malloc of %lu bytes failed\n", size);
        exit(1);
    }
    return p;
}

static void *ecalloc(size_t count, size_t size)
{
    void *p;
    
    p = calloc(count, size);
    if (p == NULL) {
        fprintf(stderr, "calloc of %lu bytes failed\n", size);
        exit(1);
    }
    return p;
}

static inline 
unsigned int advance_list(const struct queue * const q, unsigned int pos)
{
    return ((pos + 1) % q->list_size);
}

static bool queue_is_empty(struct queue *q)
{
    /* if queue is not constructed, then queue is empty */
    if (NULL == q) 
        return true;
    return (q->start_pos == q->end_pos);
}

static bool queue_is_full(struct queue *q)
{
    /* if queue is not constructed, then consider queue is full */
    if (NULL == q) 
        return true;
    return (q->start_pos == advance_list(q, q->end_pos));
}

struct queue *init_queue(size_t list_size, size_t element_size)
{
    struct queue *q;
    size_t i;

    if ((element_size <= 0) || (list_size <= 0)) 
        return NULL;
    if (NULL == (q = emalloc(sizeof(struct queue))))
        return NULL;
    q->data = emalloc(list_size * element_size); 
    q->list = ecalloc(list_size, sizeof(q->list[0]));
    if ((NULL == q->data) || (NULL == q->list))
        return NULL;
    for (i = 0; i < list_size; i++) 
        q->list[i] = q->data + element_size * i;
    q->list_size = list_size;
    q->element_size = element_size;
    q->start_pos = 0;
    q->end_pos = 0;
    return q;
}

bool push_queue(struct queue *q, const void * const new_element)
{
    if (true == queue_is_full(q))
        return false;
    /* update the new start pos */
    q->start_pos = advance_list(q, q->start_pos);
    /* do the actual data copy */
    memcpy(q->list[q->start_pos], new_element, q->element_size);
    return true;
}

void *pop_queue(struct queue *q)
{
    void *p;

    /* if queue is empty, return NULL element */ 
    if (queue_is_empty(q))
        return NULL;
    p = q->list[q->end_pos];
    /* update the end_pos position */
    q->end_pos = advance_list(q, q->end_pos);
    return p;
}

void destroy_queue(struct queue *q)
{
    if ((NULL == q) || (NULL == q->list) || (NULL == q->data)) {
        fprintf(stderr, "cannot destroy queue\n");
        exit(1);
    }
    free(q->list);
    free(q->data);
    free(q);
}

void debug_queue(struct queue *q)
{
    unsigned int i;

    if (NULL == q) 
        return;
    printf("element addr is %p, list addr is %p\n", q->data, q->list);
    for (i = 0; i < q->list_size; i++) { 
        printf("q list[%d] at    %p\n", 
               i, q->list[i]);
    }
    printf("\n");
}
