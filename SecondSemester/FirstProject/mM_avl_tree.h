//
//  mM_avl_tree.h
//  
//
//  Created by Denise F. de Rezende on 12/08/21.
//


#ifndef mM_avl_tree_h
#define mM_avl_tree_h

typedef void *type_mMavltree;

// ou eu tenho itens ou eu tenho uma chave e sua informacao separadamente
typedef void *type_mMavlitems; // informação que a chave guarda type_avlkeyinfo

typedef void* type_mMavlptrf_threeitems(type_mMavlitems, type_mMavlitems, type_mMavlitems);
typedef void* type_mMavlptrf_twoitems(type_mMavlitems, type_mMavlitems);
typedef void* type_mMavlptrf_oneitem(type_mMavlitems);
typedef void* type_mMavlptrf_oneitem_oneint(type_mMavlitems, int);


// typedef void *type_avlkey; // a chave em si
// typedef void *type_avlkeyinfo;

// Pre-condition: None
// Post-condition: The avl tree exists.
type_mMavltree create_mM_avl_tree();


// Pre-condition: The avl tree has to have been created
// Post-condition: None
// Returns a boolean: True if the avl tree is empty and false otherwise.
int empty_mM_avl_tree(type_mMavltree tree);

// Note that: 'compare' receives two items, the first is always the item to be inserted.
// if item to be inserted is greater than current item, compare should return number > 0
// if item to be inserted is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'
type_mMavltree insert_item_in_mM_avl_tree(type_mMavltree tree, type_mMavlitems item, type_mMavlptrf_twoitems compare);


// Pre-condition: The avl tree exists.
// Post-condition: The item has been deleted.
// Note that: 'compare' receives two items, the first is always the item sent by the user as 'item'.
// if 'item' is greater than current item, compare should return number > 0
// if item is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'
type_mMavltree delete_item_in_mM_avl_tree(type_mMavltree tree, type_mMavlitems item, type_mMavlptrf_twoitems compare);


// Pre-condition: The avl tree exists.
// Post-condition: None.
// Note that: the action function can include a deletion:
// must return fail or success if it includes a deletion (0 or 1 respectively)
// if it does not include deletion, function must contain a return fail (0).
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
void traverse_mMavltree_with_conditional_action(type_mMavltree tree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion);

// debugging function that can be ignored.
void preorder_debug_fuction_mMavltree(type_mMavltree tree, type_mMavlptrf_oneitem print_item);

type_mMavlitems get_right_child_in_mM_avl_tree(type_mMavltree tree);
type_mMavlitems get_left_child_in_mM_avl_tree(type_mMavltree tree);


// EVANDRO
// void destroi_avl_tree(type_mMavltree tree);

// int check_if_key_exits_in_avl_tree(type_mMavltree tree, type_avlkey key);
// // depth
// // void traverse_depth(profundidade)_avl_tree()
// // void percursoSimetricoAvl(type_mMavltree t); // seria bom passar uma função que processasse cada nó visitado
// // void percursoEmProfundidade(type_mMavltree t);
// // void percorreLarg(type_mMavltree t);



// void traverse_symmetrically_avl_tree(type_mMavltree tree);


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

#endif // mM_avl_tree_h
