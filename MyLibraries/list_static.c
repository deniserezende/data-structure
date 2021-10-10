//
//  list.h
//    
//
//  Created by Denise F. de Rezende on 03/03/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"
#include <math.h>
 
typedef struct list_structure{
	type_litems *element;
	int head;
	int current;
	int tail;
	int size;
}STRUCTURE; 

int max = 2000; // Default in case the user doesn't set a list max size

void set_list_max_size(int size){
	max = size;
}

type_list create_list(){
	STRUCTURE *new_list = malloc(sizeof(STRUCTURE));
	new_list->element = malloc(sizeof(type_litems *) * max + 1);

	// The first Node is a Head Node!
	new_list->head = 0;
	new_list->current = 0;
	new_list->tail = 0;
	new_list->size = max+1;

	return new_list;
}

int full_list(type_list list){
	STRUCTURE *stru = list;
	if(stru->tail == stru->size){
		return 1;
	}
	return 0; 
}

int empty_list(type_list list){
	STRUCTURE *stru = list;
	if(stru->tail == stru->head){
		return 1;
	}
	return 0;
}

void destroi_list(type_list list){
	STRUCTURE *stru = list;
	int i;
	free(stru);
}

void insert_item_at_the_end_of_list(type_list list, type_litems item){
	STRUCTURE *stru = list;
	stru->element[stru->tail + 1] = item;
	stru->tail = stru->tail + 1;
}

type_litems get_current_item_in_list(type_list list){
	STRUCTURE *stru = list;
	return stru->element[stru->current];
}

int is_current_undefined_in_list(type_list list){
	STRUCTURE *stru = list;
	if(stru->current == stru->head){
		return 1;
	}
	return 0;
}

void set_current_to_first_item_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = stru->head + 1;
}

void set_current_to_last_item_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = stru->tail;
}

void delete_current_item_in_list(type_list list){
	STRUCTURE *stru = list;	
	int i;
	
	for(i = stru->current; i < stru->tail; i++){
		stru->element[i] = stru->element[i+1];
	}
	stru->current = stru->current - 1;
	stru->tail = stru->tail - 1;
}

int is_current_first_item_in_list(type_list list){
	STRUCTURE *stru = list;
	if(stru->current == stru->head + 1){
		return 1;
	}
	return 0;
}

int is_current_last_item_in_list(type_list list){
	STRUCTURE *stru = list;
	if(stru->current == stru->tail){
		return 1;
	}
	return 0;
}

int find_item_in_list(type_list list, type_litems item){
	STRUCTURE *stru = list;
	type_litems *new_item = item;	
	int i = stru->head + 1;

	while(stru->element[i] != new_item && i < stru->tail + 1){
		i = i + 1;
	}
	if (i == stru->tail+1){
		// Did not find the item
		return 0;
	}
	stru->current = i;
	return 1;
}

void move_current_forward_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = stru->current + 1; 
} 

void move_current_backward_in_list(type_list list){
	STRUCTURE *stru = list;
	stru->current = stru->current - 1; 
} 

void traverse_from_current_with_conditional_action_in_list(type_list list, type_lptrf_twoitems condition, type_lptrf_twoitems action){
	STRUCTURE *stru = list;
	int i;
	if(is_current_last_item_in_list(stru)) return;

	for(i = stru->current + 1; i < stru->tail + 1; i++){
		if((long)condition(stru->element[stru->current], stru->element[i])){
			action(stru->element[stru->current], stru->element[i]);
		}
		i++;
		if(empty_list(list)) return;
	}
}

// Note that: the action function can include a deletion, but must return (0 or 1) in case the item sent was deleted.
// Check function.
void traverse_list_with_conditional_action(type_list list, type_lptrf_oneitem condition, type_lptrf_oneitem action){
	STRUCTURE *stru = list;
	int i;
	if(empty_list(stru)) return;

	for(i = stru->head; i <= stru->tail; i++){
		if((long)condition(stru->element[i])){
			if((long)action(stru->element[i])){
				i--;
			}
		}
		if(empty_list(list)) return;
	}
}
