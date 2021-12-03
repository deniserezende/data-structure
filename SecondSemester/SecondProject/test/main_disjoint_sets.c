#include <stdio.h>
#include <stdlib.h>
#include "disjoint_sets.h"

typedef struct element_set{
    int DSET_VALUE;
    int value;
}ELEMENT;

int main(){
    type_disjoint_sets sets = start_disjoint_sets(10);

    ELEMENT* element = malloc(sizeof(ELEMENT));
    element->value = 0;

    ELEMENT* element1 = malloc(sizeof(ELEMENT));
    element1->value = 1;

    ELEMENT* element2 = malloc(sizeof(ELEMENT));
    element2->value = 2;

    ELEMENT* element3 = malloc(sizeof(ELEMENT));
    element3->value = 3;

    ELEMENT* element4 = malloc(sizeof(ELEMENT));
    element4->value = 4;

    ELEMENT* element5 = malloc(sizeof(ELEMENT));
    element5->value = 5;

    printf("Created the elements\n");

    element->DSET_VALUE = making_a_new_set_containing_a_new_element(sets, element);
    element1->DSET_VALUE = making_a_new_set_containing_a_new_element(sets, element1);
    element2->DSET_VALUE = making_a_new_set_containing_a_new_element(sets, element2);
    element3->DSET_VALUE = making_a_new_set_containing_a_new_element(sets, element3);
    element4->DSET_VALUE = making_a_new_set_containing_a_new_element(sets, element4);
    element5->DSET_VALUE = making_a_new_set_containing_a_new_element(sets, element5);

    printf("Inserted the elements\n");


    int representive1 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element1->DSET_VALUE);
    printf("representive1=%d\n", representive1);
    int representive3 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element3->DSET_VALUE);
    printf("representive3=%d\n", representive3);

    merging_two_sets_in_disjoint_sets(sets, element1->DSET_VALUE, element3->DSET_VALUE);
    merging_two_sets_in_disjoint_sets(sets, element2->DSET_VALUE, element4->DSET_VALUE);
    merging_two_sets_in_disjoint_sets(sets, element3->DSET_VALUE, element4->DSET_VALUE);

    printf("======================================\n");
    representive1 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element1->DSET_VALUE);
    printf("representive1=%d\n", representive1);
    representive1 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element2->DSET_VALUE);
    printf("representive1=%d\n", representive1);
    representive1 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element3->DSET_VALUE);
    printf("representive1=%d\n", representive1);
    representive1 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element4->DSET_VALUE);
    printf("representive1=%d\n", representive1);
    printf("======================================\n");

    int representive5 = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, element5->DSET_VALUE);
    printf("representive5=%d\n", representive5);
}