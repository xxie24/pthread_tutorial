#ifndef _queue_h
#define _queue_h
#include <stdbool.h>

/* 
 * we are going to store the actual data inside the queue, not by the calling
 * routine. 
 */
struct queue {
    /* the actual data the queue point to */
    void *data;
    /* an array of pointer to the element stored in the data */
    void **list;
    unsigned int list_size;
    size_t element_size;
    unsigned int start_pos;
    unsigned int end_pos;
};

/** initialize the queue. 
 * If the program run out of memory inside this function, the program will
 * terminate with an non-zero value
 * @param[in]    list_size       this is the maximum queue size 
 * @param[in]    element_size    this is the size of each eleement inside the
 *                               queue
 * @return                       the queue initialized
 */
struct queue *init_queue(size_t list_size, size_t element_size); 

/** destroy the queue 
 * param[in]    q               the pointer to queue which is initialized
 *                              previousely by the init_queue()
 */
void destroy_queue(struct queue *q);

/** primitive way of debug the queue, will print the each element's address
 * inside the queue
 * @param[in]    q              the pointer to queue which is initialized
 *                              previousely by the init_queue()
 */
void debug_queue(struct queue *q);

/** push a new item into the queue's start_pos
 * @param[in]    q              the pointer to queue which is initialized
 *                              previousely by the init_queue()
 * @param[in]    new_element    the pointer to new element which is required to
 *                              push into the queue
 * @return       == true        the push is success
 *               == false       the push is failed because the queue is full
 */ 
bool push_queue(struct queue *q, const void * const new_element);

/* pop a new item out of the queue's end_pos 
 * @param[in]    q              the pointer to queue which is initialized
 *                              previousely by the init_queue()
 * @return       != NULL        the pop is success
 *               == NULL        the pop is failed because the queue is empty 
 */
void *pop_queue(struct queue *q);
#endif

