#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"

typedef struct list_node{
	type_items *element;
	struct list_node *next;
	struct list_node *previous;
}NODE;

typedef struct list_structure{
	NODE *head;
	NODE *current;
	NODE *tail;
}STRUCTURE;

int nodes_visited = 0; 

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_list_max_size(int size){
	//ignoring this function in this implementation!
}

// Pre-condition: None
// Post-condition: The list exists and the current item is undefined
type_structure create_list(){
	// Creating a Head Node!
	NODE *object = malloc(sizeof(NODE));
	object->next = NULL;
	object->previous = NULL;

	STRUCTURE *new_list = malloc(sizeof(STRUCTURE)); 
	new_list->head = object;
	new_list->current = object;
	new_list->tail = object;

	return new_list;
}

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is full and false otherwise.
int full_list(type_structure list){
	// Since it's a dynamic implementation it is never full!
	return 0; 
}

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is empty and false otherwise.
int empty_list(type_structure list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->head;
	if (nodes->next == NULL && nodes->previous == NULL){ 
		return 1; 
	}
	return 0;
}

// Pre-condition: The list has to have been created
// Post-condition: The list does not exist
void destroi_list(type_structure list){
	STRUCTURE *stru = list;
	NODE *aux = stru->tail;
	NODE *nodes = aux;
	while(nodes != stru->head){
		nodes = aux->previous;
		free(aux);
		aux = nodes;
	}
	free(nodes);
}

// Pre-condition: The list exists and is not full
// Post-condition: The item has been inserted at the end of the list
void insert_item_at_the_end_of_list(type_structure list, type_items item){	
	STRUCTURE *stru = list;
	NODE *old_node = stru->tail;
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->element = item;

	old_node->next = new_node;
	new_node->previous = old_node;
	new_node->next = NULL;

	stru->tail = old_node->next; 
}

// Pre-condition: Current is set to an item in the list
// Post-condition: None
// Returns the item that current represents.
type_items get_current_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->current;
	return nodes->element;
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
	stru->current = (stru->head)->next;
}

// Pre-condition: Current is set to an item in the list
// Post-condition: The item has been removed and current is the element that precedes the one removed if it exists otherwise it is undefined
void delete_current_item_in_list(type_structure list){
	STRUCTURE *stru = list;	
	NODE *del = stru->current;
	if(del->next == NULL){
		stru->tail = del->previous;
	}
	else{
		(del->next)->previous = del->previous;
	}
	(del->previous)->next = del->next;
	// Setting current to the previous item
	stru->current = del->previous;
	free(del);
}

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the first item and false otherwise.
int is_current_first_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->current;
	if(nodes == (stru->head)->next){
		return 1;
	}
	return 0;
}

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the last item and false otherwise.
int is_current_last_item_in_list(type_structure list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->current;
	if(nodes->next == NULL){
		return 1;
	}
	return 0;
}

// Pre-condition: The list exists.
// Post-condition: if item exists current is set to this item otherwise current remains where it was.
// Returns a boolean: True if the item was found and false otherwise. 
int find_item_in_list(type_structure list, type_items item){
	STRUCTURE *stru = list;
	NODE *nodes = stru->head;
	type_items *new_item = item;
	while(nodes->element != new_item && nodes != NULL){
		nodes = nodes->next;
		nodes_visited++;
	}
	if(nodes == NULL){
		// Did not find the item
		return 0;
	}
	stru->current = nodes;
	return 1;
}

// Pre-condition: Current can't be undefined and current is not the last item.
// Post-condition: Current is now the next item.
void move_current_forward_in_list(type_structure list){
	STRUCTURE *stru = list;
	stru->current = (stru->current)->next; 
	nodes_visited++;
} 

// Pre-condition: Current can't be undefined and current is not the first item.
// Post-condition: Current is now the previous item.
void move_current_backward_in_list(type_structure list){
	STRUCTURE *stru = list;
	stru->current = (stru->current)->previous; 
} 

// Pre-condition: Current can't be undefined.
// Post-condition: None
// Transverses from current comparing to all the elements in front of it and when the compare is true, a action is executed to both items.
void traverse_from_current_with_conditional_action_in_list (type_structure list, type_pointertofunction compare, type_pointertofunction action){
	STRUCTURE *stru = list;
	NODE *temp = (stru->current)->next;
	int done;

	if(is_current_last_item_in_list(stru)) return;
	do{
		done = (temp->next == NULL);
		if(compare((stru->current)->element, temp->element)){
			action((stru->current)->element, temp->element);
		}
		nodes_visited++;
		temp = temp->next;
		if(empty_list(stru)) return;

	}while(!done);
}

// Pre-condition: None
// Post-condition: None
int number_of_list_items_effectively_visited(){
	return nodes_visited;
}









