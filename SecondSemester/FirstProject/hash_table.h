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

void print_hash_table(type_hashtable hash_table, type_hashtptrf_oneitem print_item);

// item cannot equal null
//int insert_item_in_hash_table(type_hashtable hash_table, type_hashitem item, long key, type_lptrf_oneitem get_item_key);

// Note that: 'compare' receives two items, the first is always the item to be inserted.
// if item to be inserted is greater than current item, compare should return number > 0
// if item to be inserted is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
int insert_item_in_hash_table(type_hashtable hash_table, type_hashitem item, long key, type_lptrf_oneitem get_item_key, type_lptrf_twoitems compare_item_unformatted_key);

type_hashitem lookup_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem this_item);

type_hashitem delete_item_in_hash_table(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_lptrf_oneitem delete_this_item);

unsigned int collision_in_hash_table(type_hashtable hash_table, type_hashitem item, char *key);

void traverse_hash_table_with_conditional_action_optimal(type_hashtable hash_table, long key, type_lptrf_oneitem get_item_key, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem action);

void traverse_full_hash_table_with_conditional_action(type_hashtable hash_table, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem action);

void traverse_full_hash_table_with_action(type_hashtable hash_table, type_hashtptrf_oneitem action);

void traverse_hash_table_with_conditional_deletion_optimal(type_hashtable hash_table, long key, type_hashtptrf_oneitem condition, type_hashtptrf_oneitem deallocate);

#endif