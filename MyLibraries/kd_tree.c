//
//  kd_tree.c
//  
//
//  Created by Denise F. de Rezende on 29/05/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "kd_tree.h"


int DIM = 2; // default!

typedef struct kd_tree_node{
    type_kdtitems *item;
    struct kd_tree_node *left;
    struct kd_tree_node *right;
}NODE;

void traverse_kdtree_with_conditional_action_kdtaux(type_kdtree kdtree, int current_dimension, type_kdtptrf_oneitem_oneint traverse_side, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action);
void continue_traverse_kdtaux(NODE *tree, int dim, type_kdtptrf_oneitem_oneint traverse_side, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action);


type_kdtree create_kdtree(int dimension){
    DIM = dimension;
    NODE *tree = malloc(sizeof(NODE));
    tree->item = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

int empty_kdtree(type_kdtree kdtree){
    NODE *tree = kdtree;
    return(tree->left  == NULL && tree->right == NULL && tree->item == NULL);
}

int full_kdtree(type_kdtree kdtree){
    return 0;
}



type_kdtree create_new_node_kdtaux(type_kdtitems *item){ // não lembro porque tem esse * (AQUI DE! Não seria sem?)
    NODE *temp = malloc(sizeof(NODE));
    temp->item = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int are_items_equal_kdtaux(type_kdtitems item1, type_kdtitems item2, type_kdtptrf_twoitems_oneint compare){
    for(int i = 0; i < DIM; i = i+1){
        if((long)compare(item1, item2, i) != 0) return 0;
    }
    return 1;
}

int insert_item_in_kdtree(type_kdtree kdtree, type_kdtitems item, int dimension, type_kdtptrf_twoitems_oneint compare){
    NODE *tree = kdtree;
    NODE *temp = tree;
    DIM = dimension;
    int dim;
    int inserted = 0;
    // Base case: tree is empty
    if(empty_kdtree(tree)){
        tree->item = item;
        return 1;
    }
    dim = 0;
    long value_of_comparison;
    while(!inserted){
        value_of_comparison = (long)compare(item, temp->item, dim);
        if(value_of_comparison < 0){
            if(temp->left == NULL){
                temp->left = create_new_node_kdtaux(item);
                inserted = 1;
            }
            else temp = temp->left;
        }
        else if(value_of_comparison > 0){
                if(temp->right == NULL){
                    temp->right = create_new_node_kdtaux(item);
                    inserted = 1;
                }
                else temp = temp->right;
            }
            else{
                if(are_items_equal_kdtaux(item, temp->item, compare)) return 0; // error! The item has already been added
                // default: if items == temp->item in one dimension, go right!
                else if(temp->right == NULL){
                        temp->right = create_new_node_kdtaux(item);
                        inserted = 1;
                    } 
                    else temp = temp->right;
            }
        dim = (dim+1)%DIM;
    }
    return 1;
}



// Note that: this functions action cannot include a deletion.
void traverse_full_kdtree_with_conditional_action(type_kdtree kdtree, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action){
    NODE *tree = kdtree;
    if(tree == NULL) return;
    if((long)condition(tree->item)){
        action(tree->item); 
    } 
    if(tree->left != NULL) traverse_full_kdtree_with_conditional_action(tree->left, condition, action); 
    if(tree->right != NULL) traverse_full_kdtree_with_conditional_action(tree->right, condition, action);
}

void traverse_kdtree_until_condition_is_met_then_take_action(type_kdtree kdtree, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action){
    NODE *tree = kdtree;
    if(tree == NULL) return;
    if((long)condition(tree->item)){
        action(tree->item); 
        return;
    } 
    else{
        if(tree->right != NULL) traverse_kdtree_until_condition_is_met_then_take_action(tree->right, condition, action);
        if(tree->left != NULL) traverse_kdtree_until_condition_is_met_then_take_action(tree->left, condition, action); 
    }
}

// Function can include deletion, but needs to return a value (0 or 1) depending if the item sent was deleted.
void traverse_kdtree_with_conditional_action(type_kdtree kdtree, int dimension, type_kdtptrf_oneitem_oneint traverse_side, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action){
    DIM = dimension;
    if(empty_kdtree(kdtree)) return;
    traverse_kdtree_with_conditional_action_kdtaux(kdtree, dimension, traverse_side, condition, action);
}

void traverse_kdtree_with_conditional_action_kdtaux(type_kdtree kdtree, int current_dimension, type_kdtptrf_oneitem_oneint traverse_side, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action){
    NODE *tree = kdtree;
    NODE *previous = tree;
    int side, dim;
    dim = current_dimension%DIM;
    
    // Base case:
    if(tree == NULL) return;

    if(tree != NULL){
        if((long)condition(tree->item)){
            if((long)action(tree->item)){
                tree = previous;
                if(tree != NULL) traverse_kdtree_with_conditional_action_kdtaux(tree, dim, traverse_side, condition, action);
            }
            else continue_traverse_kdtaux(tree, dim, traverse_side, condition, action);
        }
        else continue_traverse_kdtaux(tree, dim, traverse_side, condition, action);
    } 
}

void continue_traverse_kdtaux(NODE *tree, int dim, type_kdtptrf_oneitem_oneint traverse_side, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action){
    long side = (long)traverse_side(tree->item, dim);
    dim = (dim+1)%DIM;

    if(side == 01){ //right
        if(tree->right != NULL) traverse_kdtree_with_conditional_action_kdtaux(tree->right, dim, traverse_side, condition, action);
    }
    else if(side == 10){ //left
            if(tree->left != NULL) traverse_kdtree_with_conditional_action_kdtaux(tree->left, dim, traverse_side, condition, action);
        }
        else if(side == 11){ //both
                if(tree->right != NULL) traverse_kdtree_with_conditional_action_kdtaux(tree->right, dim, traverse_side, condition, action);
                if(tree->left != NULL) traverse_kdtree_with_conditional_action_kdtaux(tree->left, dim, traverse_side, condition, action);
            }   
}





void destroi_kdtree(type_kdtree kdtree, int dimension, type_kdtptrf_oneitem action){
    NODE *tree = kdtree;
    NODE *next_right = NULL;
    NODE *next_left = NULL; 
    int dim;
    dim = dimension%DIM;

    // Base case:
    if(tree == NULL) return;

    action(tree->item);
    next_right = tree->right;
    next_left = tree->left;
    free(tree);
    if(next_right != NULL) destroi_kdtree(next_right, dim, action);
    if(next_left != NULL) destroi_kdtree(next_left, dim, action);
}


