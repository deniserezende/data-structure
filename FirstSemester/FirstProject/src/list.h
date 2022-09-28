#ifndef LIST_H_
#define LIST_H_

typedef void* type_structure; 
typedef void* type_items;
typedef void* type_position;
typedef void* type_pointertofunction(type_items, type_items);

/* This module provides functions for dealing with lists.
	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_list_max_size(int size);

// Pre-condition: None
// Post-condition: The list exists and the current item is undefined
type_structure create_list();

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is full and false otherwise.
int full_list(type_structure list);

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is empty and false otherwise.
int empty_list(type_structure list);

// Pre-condition: The list has to have been created
// Post-condition: The list does not exist
void destroi_list(type_structure list);

// Pre-condition: The list exists and is not full
// Post-condition: The item has been inserted at the end of the list
void insert_item_at_the_end_of_list(type_structure list, type_items item);

// Pre-condition: Current is set to an item in the list
// Post-condition: None
// Returns the item that current represents.
type_items get_current_item_in_list(type_structure list);

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if current is undefined and false otherwise.
int is_current_undefined_in_list(type_structure list);

// Pre-condition: The list is not empty
// Post-condition: Current is the first item
void set_current_to_first_item_in_list(type_structure list);

// Pre-condition: Current is set to an item in the list
// Post-condition: The item has been removed and current is the element that precedes the one removed if it exists otherwise it is undefined
void delete_current_item_in_list(type_structure list);

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the first item and false otherwise.
int is_current_first_item_in_list(type_structure list);

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the last item and false otherwise.
int is_current_last_item_in_list(type_structure list);

// Pre-condition: The list exists.
// Post-condition: if item exists current is set to this item, otherwise current remains where it was.
// Returns a boolean: True if the item was found and false otherwise. 
int find_item_in_list(type_structure list, type_items item);

// Pre-condition: Current can't be undefined and current is not the last item.
// Post-condition: Current is now the next item.
void move_current_forward_in_list(type_structure list);

// Pre-condition: Current can't be undefined and current is not the first item.
// Post-condition: Current is now the previous item.
void move_current_backward_in_list(type_structure list);

// Pre-condition: Current can't be undefined.
// Post-condition: None
// Transverses from current comparing to all the elements in front of it and when the compare is true, a action is executed to both items.
void traverse_from_current_with_conditional_action_in_list(type_structure list, type_pointertofunction compare,  type_pointertofunction action);

// Pre-condition: None
// Post-condition: None
int number_of_list_items_effectively_visited();

#endif 