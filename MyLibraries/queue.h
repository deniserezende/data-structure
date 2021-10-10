//
//  queue.h
//  
//
//  Created by Denise F. de Rezende on 23/03/21.
//

#ifndef queue_h
#define queue_h

/* This module provides functions for dealing with queues.

    A queue is a collection of items that are accessed in the FIFO (first in first out). 
    A queue with no items is called an empty queue.

	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

typedef void* type_queue; 
typedef void* type_qitems;
typedef void* type_qptrf_oneitem(type_qitems);

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_queue_max_size(int size);

// Pre-condition: None
// Post-condition: The queue exists and the current item is undefined
type_queue create_queue();

// Pre-condition: The queue has to have been created
// Post-condition: None
// Returns a boolean: True if the queue is full and false otherwise.
int full_queue(type_queue queue);

// Pre-condition: The queue has to have been created
// Post-condition: None
// Returns a boolean: True if the queue is empty and false otherwise.
int empty_queue(type_queue queue);

// Pre-condition: The queue has to have been created
// Post-condition: The queue does not exist
void destroi_queue(type_queue queue);

// Pre-condition: The queue is not full
// Post-condition: The item has been inserted at the rear of the queue.
void queue_enqueue(type_queue queue, type_qitems item);

//duvida nas duas de baixo

// Pre-condition: The queue is not empty
// Post-condition: The item on the front of the queue is removed
type_qitems queue_dequeue(type_queue queue); // void or type_qitems 

// Pre-condition: The queue is not empty
// Post-condition: The item on top is returned without removing it
type_qitems peek_front_item_in_queue(type_queue queue);

// Pre-condition: The queue has to have been created
// Post-condition: None
int get_queue_current_size(type_queue queue);

// Pre-condition: The queue is not empty
// Post-condition: None
// This functions goes to each item and calls the function pointed by action with item as its parameter
// Note that: this functions starts at the end of the queue
void iterate_over_queue_doing_action(type_queue queue, type_qptrf_oneitem action);

#endif /* queue_h */
