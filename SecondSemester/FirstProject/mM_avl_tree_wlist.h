//
//  mM_avl_tree_wlist.h
//  
//
//  Created by Denise F. de Rezende on 12/08/21.
//


#ifndef mM_avl_tree_wlist_h
#define mM_avl_tree_wlist_h

#include "list.h"

typedef void *type_mMlavltree;
typedef void *type_mMlavlitems;

typedef void* type_mMlavlptrf_fiveitems(type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems);
typedef void* type_mMlavlptrf_twoitems(type_mMlavlitems, type_mMlavlitems);
typedef void* type_mMlavlptrf_oneitem(type_mMlavlitems);

typedef void* type_mMlavlptrf_threelists_and_seven_ints(type_list, type_list, type_list, int, int, int, int, int, int, int);
typedef void* type_mMlavlptrf_sixlists(type_list, type_list, type_list, type_list, type_list, type_list);

// Pre-condition: None
// Post-condition: The avl tree exists.
type_mMlavltree create_mMl_avl_tree();

// Pre-condition: The avl tree has to have been created
// Post-condition: None
// Returns a boolean: True if the avl tree is empty and false otherwise.
int empty_mMl_avl_tree(type_mMlavltree tree);

// Pre-condition: The avl tree exists
// Post-condition: The item has been inserted at the avl tree
// See (1)
type_mMlavltree insert_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare);

// Pre-condition: The avl tree exists.
// Post-condition: The item has been deleted.
// See (1) and (8)
type_mMlavltree delete_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare, type_mMlavlptrf_twoitems delete_this_item);

// Pre-condition: The avl tree exists.
// Post-condition: None.
// See (2) and (5) and (7)
void traverse_mMlavltree_with_conditional_action(type_mMlavltree tree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action);

// Debugging function that can be ignored.
void preorder_debug_fuction_mMlavltree(type_mMlavltree tree, type_mMlavlptrf_oneitem print_item);

// Pre-condition: The mMl_avl_tree has to have been created
// Post-condition: None
// Note that: this is a very specific function. It was only created so we could use graphviz to create a diagram of the avl tree.
// See (4) and (5)
void traverse_mMlavltree_full_tree_with_action_in_parent_list_and_childs_lists(type_mMlavltree avltree, type_mMlavlptrf_sixlists action, type_mMlavlptrf_oneitem get_item_key);

// Pre-condition: The mMl_avl_tree has to have been created
// Post-condition: The mMl_avl_tree does not exist
// See (3)
type_mMlavltree destroi_mMl_avl_tree(type_mMlavltree tree, type_lptrf_oneitem deallocate);


/* Functions: */

// (1) Note that: 'compare' receives two items, the first is always the item sent by the user as 'item'.
// if 'item' is greater than current item, compare should return number > 0
// if item is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'.

// (2) Note that: 'condition' receives one item
// Function should return a long value either 1 or 0.

// (3) Note that: 'deallocate' receives one item
// You can use deallocate function to get the data from item before it is deleted
// We strongly sugest you deallocate the space you malloced for the item

// (4) Note that: 'action' => type_mMlavlptrf_sixlists receives 6 lists
// The lists may be used during execution of the function afterwards they are not available.
// The lists contain:
// 1. current node list 
// 2. left node list
// 3. right node list
// 4. list with balance in that node (current), minimum value in the left subtree, maximum value in the left subtree, minimum value in the right subtree, maximum value in the right subtree
// 5. list with balance in that node (left node), minimum value in the left subtree, maximum value in the left subtree, minimum value in the right subtree, maximum value in the right subtree
// 6. list with balance in that node (right node), minimum value in the left subtree, maximum value in the left subtree, minimum value in the right subtree, maximum value in the right subtree

// (5) Note that: 'action' receives one item
// Function cannot include a deletion.

// (6) Note that: 'get_item_key' receives one item
// Must return the item key which has to be a long or a value convertable to (void*)

// (7) Note that: 'traverse_side' => type_mMlavlptrf_fiveitems receives five items
// This function determines which side to traverse to.
// if traverse_side should be right, returns 01
// if traverse_side should be left, returns 10
// if traverse_side should be both, returns 11
// Traverse gives you five items to make the decision to where you want to traverse given a tree:
// 1. The current root
// 2. The minimum value of the left subtree
// 3. The maximum value of the left subtree
// 4. The minimum value of the right subtree
// 5. The maximum value of the right subtree
// These items are given to you in 'this exact order'.

// (8) Note that: 'delete_this_item' receives one item
// Must return if the item sent is or is not the right one to delete
// Note that: the return value must be a long either 1 or 0.

#endif // mM_avl_tree_wlist_h
