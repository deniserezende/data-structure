#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"

typedef struct list_structure{
	type_items *element;
	int head;
	int current;
	int tail;
	int size;
}STRUCTURE; 

int max = 2000; // Default in case the user doesn't set a list max size
int nodes_visited = 0; 

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_list_max_size(int size){
	max = size;
}

// Pre-condition: None
// Post-condition: The list exists and the current item is undefined
type_structure create_list(){
	STRUCTURE *new_list = malloc(sizeof(STRUCTURE));
	new_list->element = malloc(sizeof(type_items *) * max + 1);

	// The first Node is a Head Node!
	new_list->head = 0;
	new_list->current = 0;
	new_list->tail = 0;
	new_list->size = max+1;

	return new_list;
}

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is full and false otherwise.
int full_list(type_structure list){
	STRUCTURE *stru = list;
	if(stru->tail == stru->size){
		return 1;
	}
	return 0; 
}

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is empty and false otherwise.
int empty_list(type_structure list){
	STRUCTURE *stru = list;
	if(stru->tail == stru->head){
		return 1;
	}
	return 0;
}

// Pre-condition: The list has to have been created
// Post-condition: The list does not exist
void destroi_list(type_structure list){
	STRUCTURE *stru = list;
	int i;
	free(stru);
}

// Pre-condition: The list exists and is not full
// Post-condition: The item has been inserted at the end of the list
void insert_item_at_the_end_of_list(type_structure list, type_items item){
	STRUCTURE *stru = list;
	stru->element[stru->tail + 1] = item;
	stru->tail = stru->tail + 1;
}

// Pre-condition: Current is set to an item in the list
// Post-condition: None
// Returns the item that current represents.
type_items get_current_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	return stru->element[stru->current];
}

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if current is undefined and false otherwise.
int is_current_undefined_in_list(type_structure list){
	STRUCTURE *stru = list;
	if(stru->current == stru->head){
		return 1;
	}
	return 0;
}

// Pre-condition: The list is not empty
// Post-condition: Current is the first item
void set_current_to_first_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	stru->current = stru->head + 1;
}

// Pre-condition: Current is set to an item in the list
// Post-condition: The item has been removed and current is the element that precedes the one removed if it exists otherwise it is undefined
void delete_current_item_in_list(type_structure list){
	STRUCTURE *stru = list;	
	int i;
	
	for(i = stru->current; i < stru->tail; i++){
		stru->element[i] = stru->element[i+1];
	}
	stru->current = stru->current - 1;
	stru->tail = stru->tail - 1;
}

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the first item and false otherwise.
int is_current_first_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	if(stru->current == stru->head + 1){
		return 1;
	}
	return 0;
}

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the last item and false otherwise.
int is_current_last_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	if(stru->current == stru->tail){
		return 1;
	}
	return 0;
}

// Pre-condition: The list exists.
// Post-condition: If item exists current is set to this item otherwise current remains where it was.
// Returns a boolean: True if the item was found and false otherwise. 
int find_item_in_list(type_structure list, type_items item){
	STRUCTURE *stru = list;
	type_items *new_item = item;	
	int i = stru->head + 1;

	while(stru->element[i] != new_item && i < stru->tail + 1){
		i = i + 1;
		nodes_visited++;
	}
	if (i == stru->tail+1){
		// Did not find the item
		return 0;
	}
	stru->current = i;
	return 1;
}

// Pre-condition: Current can't be undefined and current is not the last item.
// Post-condition: Current is now the next item.
void move_current_forward_in_list(type_structure list){
	STRUCTURE *stru = list;
	stru->current = stru->current + 1; 
	nodes_visited++;
} 

// Pre-condition: Current can't be undefined and current is not the first item.
// Post-condition: Current is now the previous item.
void move_current_backward_in_list(type_structure list){
	STRUCTURE *stru = list;
	stru->current = stru->current - 1; 
} 

// Pre-condition: Current can't be undefined.
// Post-condition: None
// Transverses from current comparing to all the elements in front of it and when the compare is true, a action is executed to both items.
void traverse_from_current_with_conditional_action_in_list(type_structure list, type_pointertofunction compare, type_pointertofunction action){
	STRUCTURE *stru = list;
	int i;
	if(is_current_last_item_in_list(stru)) return;

	for(i = stru->current + 1; i < stru->tail + 1; i++){
		if(compare(stru->element[stru->current], stru->element[i])){
			action(stru->element[stru->current], stru->element[i]);
		}
		i++;
		nodes_visited++;
		if(empty_list(list)) return;
	}
}

// Pre-condition: None
// Post-condition: None
int number_of_list_items_effectively_visited(){
	return nodes_visited;
}










