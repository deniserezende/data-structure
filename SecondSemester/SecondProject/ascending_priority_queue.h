#ifndef ascending_priority_queue_h
#define ascending_priority_queue_h

/*
    Ascending order priority queue: 
    In ascending order priority queue, a lower priority number is given as a higher priority in a priority. 
    For example, we take the numbers from 1 to 5 arranged in an ascending order like 1,2,3,4,5; 
    therefore, the smallest number, i.e., 1 is given as the highest priority in a priority queue.
*/

#include "descending_priority_queue.h"

typedef void* type_apqueue; 
typedef void* type_apqitems;
typedef void* type_apqptrf_twoitems(type_apqitems, type_apqitems);
typedef void* type_apqptrf_oneitem(type_apqitems);


// Pre-condition: None
// Post-condition: A new max has been set
void set_ascending_priority_queue_max_size(int size);

// Pre-condition: If you want to set the max size of your queue you have to call set_ascending_priority_queue_max_size
// Otherwise the default is 2000. This cannot be changed after creating the priority queue.
// Post-condition: The priority queue exists.
type_apqueue create_ascending_priority_queue();

// Pre-condition: The priority queue has to have been created
// Post-condition: None
// Returns a boolean: True if the priority queue is full and false otherwise.
int full_ascending_priority_queue(type_apqueue queue);

// Pre-condition: The priority queue has to have been created
// Post-condition: None
// Returns a boolean: True if the priority queue is empty and false otherwise.
int empty_ascending_priority_queue(type_apqueue queue);

// Pre-condition: The mMl_avl_tree has to have been created
// Post-condition: The mMl_avl_tree does not exist
// This function does not deallocate elements that you allocated yourself
void destroi_ascending_priority_queue(type_apqueue queue);

// Pre-condition: The mMl_avl_tree has to have been created
// Post-condition: The item has been inserted in the priority queue
int insert_item_in_ascending_priority_queue(type_apqueue queue, long priority, type_apqitems item);

// Pre-condition: The item was to have been inserted in the priority queue
// Post-condition: The item has a new priority
// See (1)
int change_item_priority_in_ascending_priority_queue(type_apqueue queue, long new_priority, type_apqitems item, type_apqptrf_twoitems check_if_equal);

// Pre-condition: The item was to have been inserted in the priority queue
// Post-condition: Depending on condition the item has to have a new priority
// See (1) and (2)
int conditionally_change_item_priority_in_ascending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal, type_dpqptrf_oneitem condition);

// Pre-condition: The priority queue has to have been created
// Post-condition: The item has been removed from the priority queue and returned to the user
// However if the priority queue is empty then NULL is returned
type_apqitems pull_item_in_ascending_priority_queue(type_apqueue queue);


// Pre-condition: The priority queue has to have been created
// Post-condition: The item has NOT been removed from the priority queue, item is returned to the user
// However if the priority queue is empty then NULL is returned
type_apqitems peek_item_in_ascending_priority_queue(type_apqueue queue);

// Pre-condition: The priority queue has to have been created and cannot be empty
// Post-condition: None
int peek_item_priority_in_ascending_priority_queue(type_apqueue queue);

// Pre-condition: The priority queue has to have been created and cannot be empty
// Post-condition: None
void print_ascending_priority_queue(type_apqueue queue, type_apqptrf_oneitem print);

// Pre-condition: The priority queue has to have been created and cannot be empty
// Post-condition: None
void print_ascending_priority_queue_with_condition(type_dpqueue queue, type_dpqptrf_oneitem print, type_dpqptrf_oneitem condition);


/* Functions: */

// (1) Note that: 'check_if_equal' receives two items, the first is always the item sent by the user as 'item'.
// the function should return 0 if true and 1 if false. 
// the function 'check_if_equal' should return a value convertable to 'long'.

// (2) Note that: 'condition' receives one item
// Function should return a long value either 1 or 0.

#endif 
