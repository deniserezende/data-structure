// Making a new set containing a new element; 
// Finding the representative of the set containing a given element; 
// and Merging two sets.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disjoint_sets.h"


typedef struct disjoint_set_node{
    int representative_id;
    struct disjoint_set_node *parent;
    type_dsitem *item;
}DISJOINT_SET;

typedef struct structure{
    DISJOINT_SET* *vector;
    int next_free_space;
    int size;
}ALL_SETS;


type_disjoint_sets start_disjoint_sets(int max_of_sets){
    ALL_SETS* sets = malloc(sizeof(ALL_SETS));
    sets->vector = malloc(sizeof(DISJOINT_SET) * max_of_sets);
    sets->next_free_space = 0;
    sets->size = max_of_sets;
    return sets;
}


// Making a new set containing a new element; 
int making_a_new_set_containing_a_new_element(type_disjoint_sets sets, type_dsitem item){
    ALL_SETS* sets_ = sets;
    DISJOINT_SET *disjoint_set = malloc(sizeof(DISJOINT_SET));
    disjoint_set->representative_id = sets_->next_free_space;
    disjoint_set->parent = NULL;
    disjoint_set->item = item;
    sets_->vector[sets_->next_free_space] = disjoint_set;
    sets_->next_free_space++;
    return sets_->next_free_space - 1;
}



DISJOINT_SET* _finding_the_representative_of_the_set_containing_element_in_disjoint_sets(DISJOINT_SET *p){
    if(p->parent == NULL) return p;

    p->parent = _finding_the_representative_of_the_set_containing_element_in_disjoint_sets(p->parent);
    return p->parent;
}

// Finding the representative of the set containing a given element; 
int finding_the_representative_of_the_set_containing_element_in_disjoint_sets(type_disjoint_sets sets, int index){
    ALL_SETS* sets_ = sets;
    DISJOINT_SET * parent;    

    parent = sets_->vector[index]->parent;

    _finding_the_representative_of_the_set_containing_element_in_disjoint_sets(parent);

    int representive_id = (parent->parent)->representative_id;

    return representive_id;
}


// and Merging two sets.
void merging_two_sets_in_disjoint_sets(type_disjoint_sets sets, int index_set_one, int index_set_two){
    ALL_SETS* sets_ = sets;

    int representive_id_set_one = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, index_set_one);
    int representive_id_set_two = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(sets, index_set_two);

    sets_->vector[representive_id_set_two]->parent = sets_->vector[representive_id_set_one];

    return;
}

int get_disjoint_sets_max(type_disjoint_sets sets){
    ALL_SETS* sets_ = sets;
    return sets_->size;
}