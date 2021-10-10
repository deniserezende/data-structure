//
//  binary_search_tree.c
//  
//
//  Created by Denise F. de Rezende on 17/05/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "binary_search_tree.h"

typedef struct tree_node{
	type_bstitems *item;
	struct tree_node *left;
	struct tree_node *right;
}NODE;

type_bstree create_binary_search_tree(){
    NODE *tree = malloc(sizeof(NODE));
    tree->item = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

type_bstree create_new_node_bst_aux(type_bstitems *item){
    NODE *temp = malloc(sizeof(NODE));
    temp->item = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int insert_item_in_binary_search_tree(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare){	
    NODE *bs_tree = tree;
    NODE *parent;
	NODE *current;

	// Base case: no root 
	if(empty_binary_search_tree(tree)){
		bs_tree->item = item;
		return 1;
	}
    NODE *new_node = create_new_node_bst_aux(item);

    // Other cases
    current = bs_tree;
    long value_of_comparison;
	while(1){
        parent = current;
        value_of_comparison = (long)compare(item, current->item);
		if(value_of_comparison > 0){ 
			//go right
			current = current->right;
			if(current == NULL){
				parent->right = new_node;
				return 1;
			}		
		}
		else if(value_of_comparison < 0){
			//go left
			current = current->left;
			if(current == NULL){
				parent->left = new_node;
				return 1;
			}
		}
        else{ // if(value_of_comparison == 0) 
            free(new_node);
            return 0;
        }
	}
    return 1;
}

int full_binary_search_tree(type_bstree tree){
	// Since it's a dynamic implementation it is never full!
	return 0; 
}

int empty_binary_search_tree(type_bstree tree){
    NODE *bs_tree = tree;
	if(bs_tree->item == NULL && bs_tree->left == NULL && bs_tree->right == NULL){
		return 1;
	}
	return 0;
}

void destroi_binary_search_tree(type_bstree tree, type_bstptrf_oneitem action){
    NODE *bs_tree = tree;
    NODE *next_right = NULL;
    NODE *next_left = NULL;

    // Base case:
    if(bs_tree == NULL) return;

    // this is avaliable for the user so that he can free items inserted in the tree
    action(bs_tree->item);
    next_right = bs_tree->right;
    next_left = bs_tree->left;
    free(bs_tree);
    if(next_right != NULL) destroi_binary_search_tree(next_right, action);
    if(next_left != NULL) destroi_binary_search_tree(next_left, action);
}

void in_order_auxiliary_function_bst_aux(type_bstree tree, type_bstptrf_oneitem action){
    NODE *bs_tree = tree;
    if(bs_tree == NULL) return;
    if(empty_binary_search_tree(tree)) return;
    in_order_auxiliary_function_bst_aux(bs_tree->left, action);
    action(bs_tree->item);
    in_order_auxiliary_function_bst_aux(bs_tree->right, action);
}

void in_order_traversal_binary_search_tree(type_bstree tree, type_bstptrf_oneitem action){
    in_order_auxiliary_function_bst_aux(tree, action);
}

type_bstitems search_in_binary_search_tree_aux(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare){
    NODE *bs_tree = tree;
    // Base case: root is null or item is present at root
    if(bs_tree == NULL) return NULL; 
    if(empty_binary_search_tree(tree)) return NULL;

    long value_of_comparison = (long)compare(item, bs_tree->item);

    if(value_of_comparison == 0) return bs_tree->item;

    // item is greater than root's item
    if(value_of_comparison > 0){
        return(search_in_binary_search_tree_aux(bs_tree->right, item, compare));
    }
    // item is smaller than root's item
    return(search_in_binary_search_tree_aux(bs_tree->left, item, compare));
}

type_bstitems search_in_binary_search_tree(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare){
	NODE *bs_tree = tree;
	// Base case: root is null or item is present at root
    if(bs_tree == NULL) return NULL; 
    if(empty_binary_search_tree(tree)) return NULL;

    return(search_in_binary_search_tree_aux(tree, item, compare));
}

type_bstree in_order_successor_in_binary_search_tree(type_bstree tree){
    NODE *bs_tree = tree;
    NODE *temp = bs_tree->right;
    while(temp->left != NULL){
        temp = temp->left;
    }  
    return temp;
}

void delete_item_in_binary_search_tree(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare){
   NODE *bs_tree = tree;
   // Base case
    if(bs_tree == NULL) return;

    long value_of_comparison = (long)compare(item, bs_tree->item);

    // If the item to be deleted is smaller than the root's item,
    // then it lies in left subtree
    if(value_of_comparison < 0){
        delete_item_in_binary_search_tree(bs_tree->left, item, compare);
    }
    // If the item to be deleted is greater than the root's item, 
    // then it lies in right subtree
    else if(value_of_comparison > 0){
        delete_item_in_binary_search_tree(bs_tree->right, item, compare);
    }
    // if item is same as root's item, then 
    // This is the node to be deleted
    else {
        // node with only one child or no child
        if(bs_tree->left == NULL){
            NODE *temp = bs_tree->right;
            bs_tree = bs_tree->right;
            free(temp);
        }
        else if(bs_tree->right == NULL){
            NODE *temp = bs_tree->left;
            bs_tree = bs_tree->left;
            free(temp);
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        NODE *temp = in_order_successor_in_binary_search_tree(bs_tree);
 
        // Copy the inorder
        // successor's content to this node
        bs_tree->item = temp->item;
 
        // Delete the inorder successor
        delete_item_in_binary_search_tree(bs_tree->right, temp->item, compare);
    }
}
