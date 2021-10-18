//
//  hash_table.h
//  
//
//  Created by Denise F. de Rezende on 01/09/21.
//

#ifndef hash_table_h
#define hash_table_h
#include "list.h"

typedef void *type_hashtable;
typedef void *type_hashitem; // informação que a chave guarda type_avlkeyinfo
typedef void *type_hashtptrf_oneitem(type_hashitem);

type_hashtable create_hash_table();

// Pre-condition: The hash table exists and is not full
// Post-condition: The item has been inserted at the hash table
// See (1) and (5)
int insert_item_in_hash_table(type_hashtable hash_table, type_hashitem item, long key, type_lptrf_oneitem get_item_key, type_lptrf_twoitems compare_item_unformatted_key);

// Pre-condition: The hash_table has to have been created
// Post-condition: None
// See (5) and (7)
type_hashitem lookup_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem this_item);

// Pre-condition: The hash_table has to have been created and is not empty
// Post-condition: The item has been removed
// See (5) and (6)
type_hashitem delete_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem delete_this_item);

// Pre-condition: The hash_table has to have been created
// Post-condition: None
// Note that: Does not have to be used by the user 
// This is automatically done in the data structure
unsigned int collision_in_hash_table(type_hashtable hash_table, type_hashitem item, char *key);

// Pre-condition: The hash_table has to have been created
// Post-condition: None
// Note that: This function does not traverse the hole hash table, only the part that has the key sent
// See (4): This function cannot include a deletion.
// See (2) and (5)
void traverse_hash_table_with_conditional_action_optimal(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem action);

// Pre-condition: The hash_table has to have been created
// Post-condition: None
// Note that: This function does not traverse the hole hash table, only the part that has the key sent
// See (4): This function cannot include a deletion.
// See (2)
void traverse_full_hash_table_with_conditional_action(type_hashtable hash_table, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem action);

// Pre-condition: The hash_table has to have been created
// Post-condition: None
// See (4): This function cannot include a deletion.
void traverse_full_hash_table_with_action(type_hashtable hash_table, type_hashtptrf_oneitem action);

// Pre-condition: The hash_table has to have been created
// Post-condition: Items that meet condition sent have to have been deleted 
// Note that: This function does not traverse the hole hash table, only the part that has the key sent
// See (2) and (3)
void traverse_hash_table_with_conditional_deletion_optimal(type_hashtable hash_table, long key, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem deallocate);

// Pre-condition: The hash_table has to have been created
// Post-condition: Items that meet condition sent have to have been deleted
// See (2) and (3)
void traverse_full_hash_table_with_conditional_deletion(type_hashtable hash_table, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem deallocate);

// Pre-condition: The hash_table has to have been created
// Post-condition: None
void print_hash_table(type_hashtable hash_table, type_hashtptrf_oneitem print_item);

// Pre-condition: The hash_table has to have been created
// Post-condition: The hash_table does not exist
// See (3)
void destroi_hash_table(type_hashtable hash_table, type_hashtptrf_oneitem deallocate);


/* Functions: */

// (1) Note that: 'compare_item_unformatted_key' receives two items
// Must compare both by there unformatted key.
// if item to be inserted is greater than current item, compare should return number > 0
// if item to be inserted is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// Btw: remember the formatted key has to be a long

// (2) Note that: 'condition' receives one item
// Function should return a long value either 1 or 0.

// (3) Note that: 'deallocate' receives one item
// You can use deallocate function to get the data from item before it is deleted
// We strongly sugest you deallocate the space you malloced for the item

// (4) Note that: 'action' receives one item
// This function cannot include a deletion

// (5) Note that: 'get_item_key' receives one item
// Must return the item key which has to be a long

// (6) Note that: 'delete_this_item' receives one item
// Must return if the item sent is or is not the right one to delete
// Note that: the return value must be a long either 1 or 0.

// (7) Note that: 'this_item' receives one items
// Must return if the item sent is or is not the one you are looking for.
// Note that: the return value must be a long either 1 or 0.

#endif