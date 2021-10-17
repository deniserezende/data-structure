//
//  list_dynamic.c
//   
//
//  Created by Denise F. de Rezende on 03/03/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"

typedef struct list_node{
	type_litems *element;
	struct list_node *next;
	struct list_node *previous;
}NODE;

typedef struct list_structure{
	NODE *head;
	NODE *current;
	NODE *tail;
	int size;
}STRUCTURE;

void set_list_max_size(int size){
	// Ignoring this function in this implementation!
}

type_list create_list(){
	// Creating a Head Node!
	NODE *object = malloc(sizeof(NODE));
	object->next = NULL;
	object->previous = NULL;

	STRUCTURE *new_list = malloc(sizeof(STRUCTURE)); 
	new_list->head = object;
	new_list->current = object;
	new_list->tail = object;
	new_list->size = 0;

	return new_list;
}

int full_list(type_list list){
	// Since it's a dynamic implementation it is never full!
	return 0; 
}

int empty_list(type_list list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->head;
	if (nodes->next == NULL && nodes->previous == NULL){ 
		return 1; 
	}
	return 0;
}

void destroi_list(type_list list){
	STRUCTURE *stru = list;
	NODE *aux = stru->tail;
	NODE *nodes = aux;
	while(nodes != stru->head){
		nodes = aux->previous;
		free(aux);
		aux = nodes;
	}
	free(nodes);
	free(stru);
}

void insert_item_at_the_end_of_list(type_list list, type_litems item){	
	STRUCTURE *stru = list;
	NODE *old_node = stru->tail;
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->element = item;

	old_node->next = new_node;
	new_node->previous = old_node;
	new_node->next = NULL;

	stru->tail = old_node->next; 
	stru->size += 1;
}

type_litems get_current_item_in_list(type_list list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->current;
	return nodes->element;
}

int is_current_undefined_in_list(type_list list){
	STRUCTURE *stru = list;
	if(stru->current == stru->head){
		return 1;
	}
	return 0;
}

int is_current_equal_to_NULL(type_list list){
	STRUCTURE *stru = list;
	if(stru->current == NULL) return 1;
	return 0;	
}

void set_current_to_first_item_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = (stru->head)->next;
}

void set_current_to_last_item_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = stru->tail;
}

void delete_current_item_in_list(type_list list){
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
	stru->size -= 1;
}

type_litems delete_allocated_current_item_in_list(type_list list){
	STRUCTURE *stru = list;	
	NODE *del = stru->current;
	type_litems del_item;
	if(del->next == NULL){
		stru->tail = del->previous;
	}
	else{
		(del->next)->previous = del->previous;
	}
	(del->previous)->next = del->next;
	// Setting current to the previous item
	stru->current = del->previous;
	del_item = del->element;
	free(del);
	stru->size -= 1;
	return del_item;
}

void delete_item_in_list(type_list list, type_litems item, type_lptrf_twoitems compare){

	STRUCTURE *stru = list;
	NODE *temp = (stru->head)->next;
	NODE *previous = stru->head;
	int done;

	if(empty_list(list)) return;
	do{
		done = (temp->next == NULL);
		if((long)compare(item, temp->element) == 0){
			NODE *del = temp;
			if(del->next == NULL){
				stru->tail = del->previous;
			}
			else{
				(del->next)->previous = del->previous;
			}
			(del->previous)->next = del->next;
			// Setting current to the previous item
			if(stru->current == del){
				stru->current = del->previous;
			}
			free(del);
			temp = previous;
			stru->size -= 1;
		}
		previous = temp;
		temp = temp->next;
		if(empty_list(stru)) return;

	}while(!done);
}

int is_current_first_item_in_list(type_list list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->current;
	if(nodes == (stru->head)->next){
		return 1;
	}
	return 0;
}

int is_current_last_item_in_list(type_list list){
	STRUCTURE *stru = list;
	NODE *nodes = stru->current;
	if(nodes->next == NULL){
		return 1;
	}
	return 0;
}

int find_item_in_list(type_list list, type_litems item){
	STRUCTURE *stru = list;
	NODE *nodes = stru->head;
	type_litems *new_item = item;
	while(nodes->element != new_item && nodes != NULL){
		nodes = nodes->next;
	}
	if(nodes == NULL){
		// Did not find the item
		return 0;
	}
	stru->current = nodes;
	return 1;
}

void move_current_forward_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = (stru->current)->next; 
} 

void move_current_backward_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = (stru->current)->previous; 
} 

void traverse_from_current_with_conditional_action_in_list(type_list list, type_lptrf_twoitems condition, type_lptrf_twoitems action){
	STRUCTURE *stru = list;
	NODE *temp = (stru->current)->next;
	int done;

	if(is_current_last_item_in_list(stru)) return;
	do{
		done = (temp->next == NULL);
		if((long)condition((stru->current)->element, temp->element)){
			action((stru->current)->element, temp->element);
		}
		temp = temp->next;
		if(empty_list(stru)) return;

	}while(!done);
}

// Note that: the action function can include a deletion, but must return (0 or 1) in case the item sent was deleted.
void traverse_full_list_with_conditional_action(type_list list, type_lptrf_oneitem condition, type_lptrf_oneitem action){
	STRUCTURE *stru = list;
	NODE *temp = (stru->head)->next;
	NODE *previous = stru->head;
	int done;

	if(empty_list(list)) return;
	do{
		done = (temp->next == NULL);
		if((long)condition(temp->element)){
			if((long)action(temp->element)){
				temp = previous;
			}
		}
		previous = temp;
		temp = temp->next;
		if(empty_list(stru)) return;

	}while(!done);
}

int list_current_size(type_list list){
	STRUCTURE *stru = list;
	return stru->size;
}