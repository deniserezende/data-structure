#include <stdio.h>
#include <stdlib.h>
#include "descending_priority_queue.h"

typedef struct mybox{
    int numero;
}MYBOX;

void print(MYBOX* item){
    printf("%d", item->numero);
}

long compare(MYBOX* item, MYBOX* item2){
    return item->numero - item2->numero;
}

int main(){
    set_descending_priority_queue_max_size(10);
    type_dpqueue queue = create_descending_priority_queue();
    
    MYBOX *n1 = malloc(sizeof(MYBOX));
    n1->numero = 7;

    MYBOX *n2 = malloc(sizeof(MYBOX));
    n2->numero = 3;

    MYBOX *n3 = malloc(sizeof(MYBOX));
    n3->numero = 10;

    MYBOX *n4 = malloc(sizeof(MYBOX));
    n4->numero = 1;

    insert_item_in_descending_priority_queue(queue, 7, n1);
    insert_item_in_descending_priority_queue(queue, 3, n2);
    print_descending_priority_queue(queue, (void*)print);

    insert_item_in_descending_priority_queue(queue, 10, n3);
    print_descending_priority_queue(queue, (void*)print);

    insert_item_in_descending_priority_queue(queue, 1, n4);

    print_descending_priority_queue(queue, (void*)print);

    n2->numero = 12;
    change_item_priority_in_descending_priority_queue(queue, 12, n2, (void*)compare);
    print_descending_priority_queue(queue, (void*)print);
    
    n3->numero = 2;
    change_item_priority_in_descending_priority_queue(queue, 2, n3, (void*)compare);
    

    MYBOX *n_ta_no_queue = malloc(sizeof(MYBOX));
    n_ta_no_queue->numero = 100;
    change_item_priority_in_descending_priority_queue(queue, 2, n_ta_no_queue, (void*)compare);


    print_descending_priority_queue(queue, (void*)print);

    MYBOX *peek = peek_item_in_descending_priority_queue(queue);
    printf("peeked=%d\n", peek->numero);

    print_descending_priority_queue(queue, (void*)print);


    MYBOX *pull = pull_item_in_descending_priority_queue(queue);
    printf("pull=%d\n", pull->numero);
    print_descending_priority_queue(queue, (void*)print);

    printf("\n");
}