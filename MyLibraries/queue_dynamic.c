//
//  queue.h
//  
//
//  Created by Denise F. de Rezende on 23/03/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct queue_node{
	type_qitems *element;
	struct queue_node *next; // next = item in front ... first pointer to item  = NULL
}NODE;

typedef struct list_structure{
	NODE *front;
	NODE *rear;
    int current_size; // :) sim ou nem
}STRUCTURE;

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_queue_max_size(int size){
    // Ignoring this function in this implementation!
}

// Pre-condition: None
// Post-condition: The queue exists and the current item is undefined
type_queue create_queue(){
    STRUCTURE *queue = malloc(sizeof(STRUCTURE));
    queue->front = NULL;
    queue->rear = NULL;
    queue->current_size = 0;
    return queue;
}

// Pre-condition: The queue has to have been created
// Post-condition: None
// Returns a boolean: True if the queue is full and false otherwise.
int full_queue(type_queue queue){
    // Since it's a dynamic implementation it is never full!
    return 0;
}

// Pre-condition: The queue has to have been created
// Post-condition: None
// Returns a boolean: True if the queue is empty and false otherwise.
int empty_queue(type_queue queue){
    STRUCTURE *stru = queue;
    if(stru->front == NULL && stru->rear == NULL) return 1;
    return 0;
}

// Pre-condition: The queue has to have been created
// Post-condition: The queue does not exist
void destroi_queue(type_queue queue){
    STRUCTURE *stru = queue;
	NODE *aux = stru->rear;
	NODE *nodes = aux;
	while(nodes != stru->front){
		nodes = aux->next;
		free(aux);
		aux = nodes;
	}
	free(nodes);
}

// Pre-condition: The queue is not full
// Post-condition: The item has been inserted at the rear of the queue.
void queue_enqueue(type_queue queue, type_qitems item){
	STRUCTURE *stru = queue;
	NODE *new_node = malloc(sizeof(NODE));
    if(stru->front == NULL) stru->front = new_node;
	new_node->element = item;
	new_node->next = stru->rear;
	stru->rear = new_node; 
    stru->current_size++;
}

// Pre-condition: The queue is not empty
// Post-condition: The item on the front of the queue is removed
type_qitems queue_dequeue(type_queue queue){
	STRUCTURE *stru = queue;
    NODE *temp = stru->front;
    type_qitems *item = temp->element;
    NODE *helper = stru->rear;
    if (helper == temp){ //only one item in the queue
        stru->front = NULL;
        stru->rear = NULL;
    }
    else{
        while(helper->next != temp){
            helper = helper->next;
        }
        stru->front = helper;
        helper->next = NULL;
    }
    free(temp);
    stru->current_size--;
    return item;

}

// Pre-condition: The queue is not empty
// Post-condition: The item on top is returned without removing it
type_qitems peek_front_item_in_queue(type_queue queue){
	STRUCTURE *stru = queue;
    NODE *nodes = stru->front;
    return nodes->element;
}

// Pre-condition: The queue has to have been created
// Post-condition: None
int get_queue_current_size(type_queue queue){
    STRUCTURE *stru = queue;
    return(stru->current_size);
}

// Pre-condition: The queue is not empty
// Post-condition: None
// This functions goes to each item and calls the function pointed by action with item as its parameter
// Note that: this functions starts at the end of the queue
void iterate_over_queue_doing_action(type_queue queue, type_qptrf_oneitem action){
	STRUCTURE *stru = queue;
	NODE *temp = stru->rear;
	int done;
	do{
		done = (temp->next == NULL);
		action(temp->element);
		temp = temp->next;
		if(empty_queue(stru)) return;
	}while(!done);
}