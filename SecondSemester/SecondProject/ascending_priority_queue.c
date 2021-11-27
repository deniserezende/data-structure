#include "ascending_priority_queue.h"




void set_ascending_priority_queue_max_size(int size){
    set_descending_priority_queue_max_size(size);
}

type_apqueue create_ascending_priority_queue(){
    return create_descending_priority_queue();
}

int full_ascending_priority_queue(type_apqueue queue){
    return full_descending_priority_queue(queue);
}
int empty_ascending_priority_queue(type_apqueue queue){
    return empty_descending_priority_queue(queue);
}
void destroi_ascending_priority_queue(type_apqueue queue){
    destroi_descending_priority_queue(queue);
}

// compare should return 0 if equal
// -1 if the element to be inserted is less than the other
// 1 if the elemtent to be inserted is more than the other
// element to be inserted - other
int insert_item_in_ascending_priority_queue(type_apqueue queue, long priority, type_apqitems item){
    long inverted_priority = (-1) * priority;
    return insert_item_in_descending_priority_queue(queue, inverted_priority, item);
}

// AQUIDE EFICIENCIA = DAR O VALOR ANTIGO PARA ELE!!!
int change_item_priority_in_ascending_priority_queue(type_apqueue queue, long new_priority, type_apqitems item, type_dpqptrf_twoitems check_if_equal){
    long inverted_priority = (-1) * new_priority;
    return change_item_priority_in_descending_priority_queue(queue, inverted_priority, item, check_if_equal);
}

type_apqitems pull_item_in_ascending_priority_queue(type_apqueue queue){
    return pull_item_in_descending_priority_queue(queue);
}

type_apqitems peek_item_in_ascending_priority_queue(type_apqueue queue){
    return peek_item_in_descending_priority_queue(queue);
}

int peek_item_priority_in_ascending_priority_queue(type_apqueue queue){
    return peek_item_priority_in_descending_priority_queue(queue);
}


void print_ascending_priority_queue(type_apqueue queue, type_apqptrf_oneitem print){
    print_descending_priority_queue(queue, print);
}

int conditionally_change_item_priority_in_ascending_priority_queue(type_dpqueue queue, long new_priority, type_dpqitems item, type_dpqptrf_twoitems check_if_equal, type_dpqptrf_oneitem condition){
    long inverted_priority = (-1) * new_priority;
    return conditionally_change_item_priority_in_descending_priority_queue(queue, inverted_priority, item, check_if_equal, condition);
}

void print_ascending_priority_queue_with_condition(type_dpqueue queue, type_dpqptrf_oneitem print, type_dpqptrf_oneitem condition){
    print_descending_priority_queue_with_condition(queue, print, (void*)condition);
}