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

// ou eu tenho itens ou eu tenho uma chave e sua informacao separadamente
typedef void *type_mMlavlitems; // informação que a chave guarda type_avlkeyinfo

typedef void* type_mMlavlptrf_fiveitems(type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems);
typedef void* type_mMlavlptrf_twoitems(type_mMlavlitems, type_mMlavlitems);
typedef void* type_mMlavlptrf_oneitem(type_mMlavlitems);

typedef void* type_mMlavlptrf_threelists_and_seven_ints(type_list, type_list, type_list, int, int, int, int, int, int, int);
typedef void* type_mMlavlptrf_sixlists(type_list, type_list, type_list, type_list, type_list, type_list);


// typedef void *type_avlkey; // a chave em si
// typedef void *type_avlkeyinfo;

// Pre-condition: None
// Post-condition: The avl tree exists.
type_mMlavltree create_mMl_avl_tree();


// Pre-condition: The avl tree has to have been created
// Post-condition: None
// Returns a boolean: True if the avl tree is empty and false otherwise.
int empty_mMl_avl_tree(type_mMlavltree tree);

// Note that: 'compare' receives two items, the first is always the item to be inserted.
// if item to be inserted is greater than current item, compare should return number > 0
// if item to be inserted is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'
type_mMlavltree insert_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare);


// Pre-condition: The avl tree exists.
// Post-condition: The item has been deleted.
// Note that: 'compare' receives two items, the first is always the item sent by the user as 'item'.
// if 'item' is greater than current item, compare should return number > 0
// if item is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'
//type_mMlavltree delete_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare);
type_mMlavltree delete_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare, type_mMlavlptrf_twoitems verify_item);

// Pre-condition: The avl tree exists.
// Post-condition: None.
// Note that: the action function cannot include a deletion.
// Note that: the traverse_side function determines which side to traverse to.
// if traverse_side should be right, returns 01
// if traverse_side should be left, returns 10
// if traverse_side should be both, returns 11
// Traverse gives you tree items to make the decision to where you want to traverse given a tree:
// 1. The current root
// 2. The minimum value of the tree descending that root
// 3. The maximum value of the tree descending that root
// These items are given to you in 'this exact order'.
// Transverses avl tree depending on traverse side, checks a condition and if true takes action.
void traverse_mMlavltree_with_conditional_action(type_mMlavltree tree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action);

// debugging function that can be ignored.
void preorder_debug_fuction_mMlavltree(type_mMlavltree tree, type_mMlavlptrf_oneitem print_item);

// type_mMlavlitems get_right_child_in_mM_avl_tree(type_mMlavltree tree);
// type_mMlavlitems get_left_child_in_mM_avl_tree(type_mMlavltree tree);

void traverse_mMlavltree_full_tree_with_action_in_parent_list_and_childs_lists(type_mMlavltree avltree, type_mMlavlptrf_sixlists action, type_mMlavlptrf_oneitem get_key);
// EVANDRO
// void destroi_avl_tree(type_mMlavltree tree);

// int check_if_key_exits_in_avl_tree(type_mMlavltree tree, type_avlkey key);
// // depth
// // void traverse_depth(profundidade)_avl_tree()
// // void percursoSimetricoAvl(type_mMlavltree t); // seria bom passar uma função que processasse cada nó visitado
// // void percursoEmProfundidade(type_mMlavltree t);
// // void percorreLarg(type_mMlavltree t);



// void traverse_symmetrically_avl_tree(type_mMlavltree tree);


// EVANDRO
// AvlTree newAvlTree();
// bool isEmptyAvl(AvlTree t);
// bool insertAvl(AvlTree t, Key k, Info i);
// bool existsKeyAvl(AvlTree t, Key k);
// bool removeAvl(AvlTree t, Key k);
// Info getAvl(AvlTree t, Key k);
// void percursoSimetricoAvl(AvlTree t); // seria bom passar uma função que processasse cada nó visitado
// void percursoEmProfundidade(AvlTree t);
// void percorreLarg(AvlTree t);
// void killAvlTree(AvlTree t);

#endif // mM_avl_tree_wlist_h
