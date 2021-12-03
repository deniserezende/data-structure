#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "descending_priority_queue.h"
#include <math.h>
 
typedef struct queue_node{
	type_dpqitems item;
	long priority;
}NODE; 

typedef struct queue_structure{
	type_dpqitems *vector; //AQUIDE não era para ser NODE*
	//int current;
	int next_item;
	int size;
	int next_free_space;
}STRUCTURE; 

int max = 2000; // Default in case the user doesn't set a queue max size

void set_descending_priority_queue_max_size(int size){
	max = size;
}

void _reset_priority_in_pqueue(type_dpqueue queue){
	STRUCTURE *stru = queue;
	for(int i=0; i < stru->size; i++){
		stru->vector[i] = NULL;
	}
}


type_dpqueue create_descending_priority_queue(){
	STRUCTURE *new_queue = malloc(sizeof(STRUCTURE));
	new_queue->vector = malloc(sizeof(NODE *) * max + 1);
	printf("criei\n");
	// new_queue->current = 0;
	new_queue->next_item = -1; // Empty queue
	new_queue->size = max+1;
	new_queue->next_free_space = new_queue->next_item + 1;
	printf("other\n");
	_reset_priority_in_pqueue(new_queue);
	printf("reset ok\n");
	return new_queue;
}


int full_descending_priority_queue(type_dpqueue queue){
	STRUCTURE *stru = queue;
	if(stru->next_item == stru->size){
		return 1;
	}
	return 0; 
}

int empty_descending_priority_queue(type_dpqueue queue){
	STRUCTURE *stru = queue;
	if(stru->next_item == -1){
		return 1;
	}
	return 0;
}

void destroi_descending_priority_queue(type_dpqueue queue){
	printf("testar!!!!!!\n");
	STRUCTURE *stru = queue;

	for(int i=0; i < stru->next_item+1; i++){
		NODE *item = stru->vector[i];
		free(item);
	}
	free(stru->vector);
	free(stru);
}

void _insertion_sort_item_by_priority_in_pqueue(STRUCTURE *stru, int unsorted_item_index){
	NODE *aux;
	NODE *unsorted_item = stru->vector[unsorted_item_index];

	for(int i=unsorted_item_index-1; i >= 0; i--){
		NODE *current = stru->vector[i];
		if(unsorted_item->priority < current->priority){
			aux = stru->vector[unsorted_item_index];
			stru->vector[unsorted_item_index] = stru->vector[i];
			stru->vector[i] = aux;
			unsorted_item_index = i;
		}
		else break;
	}
}

// compare should return 0 if equal
// -1 if the element to be inserted is less than the other
// 1 if the elemtent to be inserted is more than the other
// element to be inserted - other
int insert_item_in_descending_priority_queue(type_dpqueue queue, long priority, type_dpqitems item){
	STRUCTURE *stru = queue;

	if (stru->next_free_space > stru->size) return 0;
	
	// inserted the element
	NODE* item_node = malloc(sizeof(NODE));
	item_node->item = item;
	item_node->priority = priority;
	stru->vector[stru->next_free_space] = item_node;

	// correcting its place
	_insertion_sort_item_by_priority_in_pqueue(stru, stru->next_free_space);

	stru->next_item = stru->next_item + 1;
	stru->next_free_space = stru->next_item + 1;
	return 1;
}

int _find_item_in_descending_priority_queue(type_dpqueue queue, type_dpqitems item, type_dpqptrf_twoitems check_if_equal){
	STRUCTURE *stru = queue;
	int lower = 0;
	int upper = stru->next_item;

	// for(int i=0; i <= stru->next_item; i++){
	// 	NODE *current = stru->vector[i];
	// 	if((long)check_if_equal(item, current->item) == 0){
	// 		return i;
	// 	}
	// }
	// return -1;
	for(int i=stru->next_item; i >= 0; i--){
		NODE *current = stru->vector[i];
		if(((long)check_if_equal(item, current->item)) == 0){
			return i;
		}
	}
	return -1;
}


void _sort_item_by_priority_in_p_queue(STRUCTURE *stru, int unsorted_item_index){
	NODE *aux;
	NODE *unsorted_item = stru->vector[unsorted_item_index];

	int unsorted_item_index_one = unsorted_item_index;

	for(int i=unsorted_item_index; i < stru->next_item; i++){
		NODE *posterior_item = stru->vector[i+1];
		if(unsorted_item->priority > posterior_item->priority){
			aux = stru->vector[unsorted_item_index_one];
			stru->vector[unsorted_item_index_one] = stru->vector[i+1];
			stru->vector[i+1] = aux;
			unsorted_item_index_one = i+1;
		}
		else break;
	}
	int unsorted_item_index_two = unsorted_item_index;
	for(int j=unsorted_item_index; j > 1; j--){
		NODE *previous_item = stru->vector[j-1];
		if(unsorted_item->priority < previous_item->priority){
			aux = stru->vector[unsorted_item_index_two];
			stru->vector[unsorted_item_index_two] = stru->vector[j-1];
			stru->vector[j-1] = aux;
			unsorted_item_index_two = j-1;
		}
		else break;
	}
}

	// correcting its place opcao 2
	// merge sort que pega o meio e ve para que lado deve ir
	// type_dpqitems aux;
	// int size = stru->size;
	// int last_element = stru->size - 1;
	// int current_space = stru->next_free_space;
	// for(int i=last_element; i < stru->size; i++){
	// 	if(compare(stru->vector[stru->next_free_space], stru->vector[i] < 0)){
	// 		aux = stru->vector[stru->next_free_space];
	// 		stru->vector[stru->next_free_space] = stru->vector[i];
	// 		stru->vector[i] = aux;
	// 	}
	// 	else break;
	// }

// AQUIDE EFICIENCIA = DAR O VALOR ANTIGO PARA ELE!!!
int change_item_priority_in_descending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal){
	STRUCTURE *stru = queue;
	int index = _find_item_in_descending_priority_queue(stru, item, check_if_equal);
	if(index == -1) return 0;
	// changing priority
	NODE *item_node = stru->vector[index];
	item_node->priority = new_priority;

	// sort that unsorted item
	// for now this function doesnt work for this
	_sort_item_by_priority_in_p_queue(stru, index);
	return 1;
}

// if item not found returns -1
// if didn't change returns 0
// if changed returns 1
int conditionally_change_item_priority_in_descending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal, type_dpqptrf_oneitem condition){
	STRUCTURE *stru = queue;
	int index = _find_item_in_descending_priority_queue(stru, item, check_if_equal);
	if(index == -1) return -1;
	// changing priority
	NODE *item_node = stru->vector[index];
	
	if(condition(item_node->item)){
		item_node->priority = new_priority;
		// sort that unsorted item
		// for now this function doesnt work for this
		_sort_item_by_priority_in_p_queue(stru, index);
		return 1;
	}
	return 0;
}

type_dpqitems pull_item_in_descending_priority_queue(type_dpqueue queue){
	STRUCTURE *stru = queue;
	NODE *highest = stru->vector[stru->next_item];
	free(stru->vector[stru->next_item]);
	stru->vector[stru->next_item] = NULL;
	stru->next_item = stru->next_item - 1;
	stru->next_free_space = stru->next_free_space - 1;
	return highest->item;
}

type_dpqitems peek_item_in_descending_priority_queue(type_dpqueue queue){
	STRUCTURE *stru = queue;
	NODE *highest = stru->vector[stru->next_item];
	return highest->item;
}

int peek_item_priority_in_descending_priority_queue(type_dpqueue queue){
	STRUCTURE *stru = queue;
	NODE *highest = stru->vector[stru->next_item];
	return highest->priority;
}

void print_descending_priority_queue(type_dpqueue queue, type_dpqptrf_oneitem print){
	STRUCTURE *stru = queue;

	for(int i=0; i < stru->next_item+1; i++){
		NODE *item = stru->vector[i];
		printf("\t");
		print(item->item);
	}
	printf("\n");
}

void print_descending_priority_queue_with_condition(type_dpqueue queue, type_dpqptrf_oneitem print, type_dpqptrf_oneitem condition){
	STRUCTURE *stru = queue;

	for(int i=0; i < stru->next_item+1; i++){
		NODE *item = stru->vector[i];
		if((long)condition(item->item)){
			printf("\t");
			print(item->item);
		}
	}
	printf("\n");
}


// compare should return 0 if equal
// -1 if the element to be inserted is less than the other
// 1 if the elemtent to be inserted is more than the other
// element to be inserted - other

// template<typename I>
// I BinarySearch(I begin, I end)
// {
//     I lower = begin;
//     I upper = end;
//     while (lower < upper)
//     {
//         I mid = lower + std::distance(upper, lower) / 2;
//         if(key == *mid)
//         {
//             return mid;
//         }
//         if(key < *mid) {
//             upper = mid;
//         }
//         else {
//             lower = mid;
//         }
//     }

//     return end;
// }

// int _binary_search(type_dpqitems *array, int left, int right, type_dpqitems value, type_dpqptrf_twoitems check_if_equal) { 
//     if (right >= left) { 
//         int mid = left + (right - left) / 2; 
// 		NODE *item = array[mid];
// 		long value_of_equality = check_if_equal(item->item, value);
// 		if(value_of_equality == 0){
// 			return mid;
// 		}
// 		if(item->priority > value->priority){
// 			return binarySearch(array, mid+1, right, x); 
// 		}
//         if (arr[mid] == x) 
//             return mid; 
//         if (arr[mid] > x) 
//             return binarySearch(arr, left, mid - 1, x); 
//         return binarySearch(arr, mid + 1, right, x); 
//     } 
//     return -1; 
// } 
