//
//  stack_dynamic.c
//  
//
//  Created by Denise F. de Rezende on 17/04/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct stack_node{
	type_sitems *element;
	struct stack_node *next;
}NODE;

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_stack_max_size(int size){
    // Ignoring this function in this implementation!
}

// Pre-condition: None
// Post-condition: The stack exists.
type_stack create_stack(){
    return NULL;
}

// Pre-condition: The stack has to have been created
// Post-condition: None
// Returns a boolean: True if the stack is full and false otherwise.
int full_stack(type_stack stack){
	// Since it's a dynamic implementation it is never full!
    return 0;
}

// Pre-condition: The stack has to have been created
// Post-condition: None
// Returns a boolean: True if the stack is empty and false otherwise.
int empty_stack(type_stack stack){
    NODE *top = stack;
    if(top == NULL) return 1;
    return 0;
}

// Pre-condition: The stack has to have been created
// Post-condition: The stack does not exist
void destroi_stack(type_stack stack){
    NODE *top = stack;
    NODE *aux = top;
    while(top != NULL){
        top = aux->next;
        free(aux);
        aux = top;
    }
}

// Pre-condition: The stack is not full
// Post-condition: The item has been stacked up
void push_stack(type_stack *stack, type_sitems item){
    NODE **top = (NODE**)stack;
    NODE *new_node;

    new_node = (NODE*)malloc(sizeof(NODE));
    new_node->element = item;
    new_node->next = *top;
    *top = new_node;
}

// Pre-condition: The stack is not empty
// Post-condition: The item on top of the stack is removed
type_sitems pop_stack(type_stack *stack){
    NODE **top = (NODE**)stack;
    NODE *del_node = *top;
    type_sitems *item;
    item = (*top)->element;
    (*top) = (*top)->next;
    free(del_node); 
    return item;
}

// Pre-condition: The stack is not empty
// Post-condition: The item on top is returned without removing it
type_sitems consult_item_in_stack(type_stack stack){ //get? ou peek top item????
    NODE *top = stack;
    return top->element;
}

// Pre-condition: The stack is not empty
// Post-condition: None
// This functions goes to each item and calls the function pointed by action with item as its parameter
void iterate_over_stack_doing_action(type_stack stack, type_sptrf_oneitem action){
	NODE *top = stack;
	NODE *temp = top;
	int done;
	do{
		done = (temp->next == NULL);
		action(temp->element);
		temp = temp->next;
		if(empty_stack(top)) return;
	}while(!done);
}