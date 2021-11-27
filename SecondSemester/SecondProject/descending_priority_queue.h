#ifndef descending_priority_queue_h
#define descending_priority_queue_h

/* 
	Descending order priority queue: 
	In descending order priority queue, 
	a higher priority number is given as a higher priority in a priority. 
	For example, we take the numbers from 1 to 5 arranged in descending order like 5, 4, 3, 2, 1; 
	therefore, the largest number, i.e., 5 is given as the highest priority in a priority queue.
*/

typedef void* type_dpqueue; 
typedef void* type_dpqitems;
typedef void* type_dpqptrf_twoitems(type_dpqitems, type_dpqitems);
typedef void* type_dpqptrf_oneitem(type_dpqitems);

void set_descending_priority_queue_max_size(int size);
type_dpqueue create_descending_priority_queue();

int full_descending_priority_queue(type_dpqueue queue);
int empty_descending_priority_queue(type_dpqueue queue);
void destroi_descending_priority_queue(type_dpqueue queue);
// compare should return 0 if equal
// -1 if the element to be inserted is less than the other
// 1 if the elemtent to be inserted is more than the other
// element to be inserted - other
int insert_item_in_descending_priority_queue(type_dpqueue queue, long priority, type_dpqitems item);

// AQUIDE EFICIENCIA = DAR O VALOR ANTIGO PARA ELE!!!
int change_item_priority_in_descending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal);

int conditionally_change_item_priority_in_descending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal, type_dpqptrf_oneitem condition);

type_dpqitems pull_item_in_descending_priority_queue(type_dpqueue queue);

type_dpqitems peek_item_in_descending_priority_queue(type_dpqueue queue);

int peek_item_priority_in_descending_priority_queue(type_dpqueue queue);

void print_descending_priority_queue(type_dpqueue queue, type_dpqptrf_oneitem print);

void print_descending_priority_queue_with_condition(type_dpqueue queue, type_dpqptrf_oneitem print, type_dpqptrf_oneitem condition);

#endif 
