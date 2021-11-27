#ifndef disjoint_sets
#define disjoint_sets

typedef void* type_disjoint_sets;
typedef void* type_dsitem;


type_disjoint_sets start_disjoint_sets(int max_of_sets);
int making_a_new_set_containing_a_new_element(type_disjoint_sets sets, type_dsitem item);
int finding_the_representative_of_the_set_containing_element_in_disjoint_sets(type_disjoint_sets sets, int index);
void merging_two_sets_in_disjoint_sets(type_disjoint_sets sets, int index_set_one, int index_set_two);
int get_disjoint_sets_max(type_disjoint_sets sets);

// (1) Note that: The value returned in making_a_new_set_containing_a_new_element is VERY IMPORTANT
// this value represents the element, therefore if you:
// (a) Change it
// (b) Lose it
// You lose access to the element

// Recomendation:
// Keep this value inside your type_dsitem item under DSET_VALUE
// all caps so you won't change it.

#endif 
