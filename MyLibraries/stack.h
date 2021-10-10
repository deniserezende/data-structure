// 
//  stack.h
//  
//
//  Created by Denise F. de Rezende on 17/04/21.
//

#ifndef stack_h
#define stack_h

/* This module provides functions for dealing with stacks.

    A stack is a collection of items that are accessed in the LIFO (last in first out). 
    A stack with no items is called an empty stack.

	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

typedef void* type_stack; 
typedef void* type_sitems;
typedef void* type_sptrf_oneitem(type_sitems);

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_stack_max_size(int size);

// Pre-condition: None
// Post-condition: The stack exists and the current item is undefined
type_stack create_stack();

// Pre-condition: The stack has to have been created
// Post-condition: None
// Returns a boolean: True if the stack is full and false otherwise.
int full_stack(type_stack stack);

// Pre-condition: The stack has to have been created
// Post-condition: None
// Returns a boolean: True if the stack is empty and false otherwise.
int empty_stack(type_stack stack);

// Pre-condition: The stack has to have been created
// Post-condition: The stack does not exist
void destroi_stack(type_stack stack);

// Pre-condition: The stack is not full
// Post-condition: The item has been stacked up at the top.
void push_stack(type_stack *stack, type_sitems item);

// Pre-condition: The stack is not empty
// Post-condition: The item on top of the stack is removed
type_sitems pop_stack(type_stack *stack);

// Pre-condition: The stack is not empty
// Post-condition: The item on top is returned without removing it
type_sitems peek_top_item_in_stack(type_stack stack);

// Pre-condition: The stack is not empty
// Post-condition: None
// This functions goes to each item and calls the function pointed by action with item as its parameter
void iterate_over_stack_doing_action(type_stack stack, type_sptrf_oneitem action);

#endif /* stack_h */

