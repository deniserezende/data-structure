#ifndef disjoint_sets
#define disjoint_sets

/*
A disjoint-set data structure, also called a union–find data structure or merge–find set, 
is a data structure that stores a collection of disjoint (non-overlapping) sets. 
It provides operations for adding new sets, merging sets (replacing them by their union), 
and finding a representative member of a set. The last operation allows to find out efficiently 
if any two elements are in the same or different sets.
*/

typedef void* type_disjoint_sets;
typedef void* type_dsitem;


// Pre-condition: None
// Post-condition: A disjoint set exists
type_disjoint_sets create_disjoint_sets(int max_of_sets);

// Pre-condition: The disjoint set has to have been created
// Post-condition: A new set has to have been inserted
// IMPORTANT: See (1) 
int making_a_new_set_containing_a_new_element(type_disjoint_sets sets, type_dsitem item);

// Pre-condition: The disjoint set has to have been created and both sets have to already have been inserted
// Post-condition: The sets have to have been merged
void merging_two_sets_in_disjoint_sets(type_disjoint_sets sets, int index_set_one, int index_set_two);

// Pre-condition: The disjoint set has to have been created 
// and the index sent has to belong to a set
// Post-condition: The sets have to have been merged
int finding_the_representative_of_the_set_containing_element_in_disjoint_sets(type_disjoint_sets sets, int index);

// Pre-condition: The disjoint set has to have been created
// Post-condition: None
int get_disjoint_sets_max_size(type_disjoint_sets sets);

// Pre-condition: The disjoint set has to have been created
// Post-condition: The disjoint set does not exist anymore
void destroi_disjoint_sets(type_disjoint_sets sets);

// (1) Note that: The value returned in making_a_new_set_containing_a_new_element is VERY IMPORTANT
// this value represents the element, therefore if you:
// (a) Change it
// (b) Lose it
// You lose access to the element

// Recomendation:
// Keep this value inside your type_dsitem item labeled as DSET_VALUE
// all caps so you won't change it.

#endif 
