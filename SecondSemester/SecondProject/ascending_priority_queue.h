/*
    Ascending order priority queue: 
    In ascending order priority queue, 
*/

#ifndef ascending_priority_queue_h
#define ascending_priority_queue_h

#include "descending_priority_queue.h"

typedef void* type_apqueue; 
typedef void* type_apqitems;
typedef void* type_apqptrf_twoitems(type_apqitems, type_apqitems);
typedef void* type_apqptrf_oneitem(type_apqitems);

void set_ascending_priority_queue_max_size(int size);
type_apqueue create_ascending_priority_queue();

int full_ascending_priority_queue(type_apqueue queue);
int empty_ascending_priority_queue(type_apqueue queue);
void destroi_ascending_priority_queue(type_apqueue queue);
// compare should return 0 if equal
// -1 if the element to be inserted is less than the other
// 1 if the elemtent to be inserted is more than the other
// element to be inserted - other
int insert_item_in_ascending_priority_queue(type_apqueue queue, long priority, type_apqitems item);

// AQUIDE EFICIENCIA = DAR O VALOR ANTIGO PARA ELE!!!
int change_item_priority_in_ascending_priority_queue(type_apqueue queue, long new_priority, type_apqitems item, type_apqptrf_twoitems check_if_equal);

int conditionally_change_item_priority_in_ascending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal, type_dpqptrf_oneitem condition);

type_apqitems pull_item_in_ascending_priority_queue(type_apqueue queue);

type_apqitems peek_item_in_ascending_priority_queue(type_apqueue queue);

int peek_item_priority_in_ascending_priority_queue(type_apqueue queue);

void print_ascending_priority_queue(type_apqueue queue, type_apqptrf_oneitem print);

void print_ascending_priority_queue_with_condition(type_dpqueue queue, type_dpqptrf_oneitem print, type_dpqptrf_oneitem condition);

#endif