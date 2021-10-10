//
//  mM_avl_tree.c
//  
//
//  Created by Denise F. de Rezende on 12/08/21.
//

#include<stdio.h>
#include<stdlib.h>
#include "mM_avl_tree.h"

typedef struct avl_tree_node {
    type_mMavlitems* item;
    int height;
    struct avl_tree_node *left; // left child
    struct avl_tree_node *right; // right child
    struct avl_tree_node *max; 
    struct avl_tree_node *min;
    //onde ficar null eu balanceio percorrendo ????
    // removo um elemento e salvo um apontador para o max e min do anterior
    //depois percorro como se fosse inserir aquele elemento checando se o max e min de é null
} NODE;

type_mMavltree create_mM_avl_tree(){
    return NULL;
}

type_mMavltree create_new_node_avl_aux(type_mMavlitems item){
    NODE *temp = malloc(sizeof(NODE));
    temp->item = item;
    temp->height = 1;
    temp->left = NULL;
    temp->right = NULL;
    temp->max = temp;
    temp->min = temp;
    return temp;
}

int empty_mM_avl_tree(type_mMavltree tree){
    NODE *avl_tree = tree;
    return(avl_tree == NULL);
}

int maximum_two_int_avl_aux(int a, int b){
    if(a > b) return a;
    else return b;
}

int node_height_avl_aux(type_mMavltree tree){
    NODE *avl_tree = tree;
    if(avl_tree == NULL) return 0;
    return(avl_tree->height);
}

/* Returns the minimum value item in the tree. 
   Note that: the entire tree is not searched. */
type_mMavltree min_value_in_avl_aux(NODE* node){
    NODE* current = node;
 
    // loop down to find the leftmost leaf, which is equivalent to the minimum value
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

/* Returns the maximum value item in the tree. 
   Note that: the entire tree is not searched. */
type_mMavltree max_value_in_avl_aux(NODE* node){
    NODE* current = node;
 
    // loop down to find the rightmost leaf, which is equivalent to the maximum value
    while (current->right != NULL)
        current = current->right;
 
    return current;
}

/* Returns the difference between the left and right height of the tree root given.
    Note that the calculation is: left height - right height.*/
int get_balance_in_avl_aux(type_mMavltree tree){
    NODE *avl_tree = tree;
    if(avl_tree == NULL) return 0;
    return(node_height_avl_aux(avl_tree->left) - node_height_avl_aux(avl_tree->right));
}
 
// Updates and returns node height
int update_node_height_avl_aux(NODE* node){
    node->height = maximum_two_int_avl_aux(node_height_avl_aux(node->left), node_height_avl_aux(node->right))+1;
    return node->height;
}

// aqui não to entendendo:
NODE *right_rotate_subtree_in_avl_tree_aux(NODE *root){
    NODE *root_left = root->left;
    NODE *temp = root_left->right;
    printf("is temp null: %d\n", temp == NULL);
 
    // Rotation: 
    root->left = temp;
    root_left->right = root;
 
    // Updating max and min
    if(root_left->right != NULL) root_left->max = (root_left->right)->max;
    else root_left->max = root_left;

    if(root->left != NULL) root->min = (root->left)->min;
    else root->min = root;
    
    // Updating heights:
    update_node_height_avl_aux(root);
    update_node_height_avl_aux(root_left);

    return root_left; //new root
}


 
NODE *left_rotate_subtree_in_avl_tree_aux(NODE *root){
    NODE *root_right = root->right;
    NODE *temp = root_right->left;
 
    // Rotation:
    root_right->left = root;
    root->right = temp;

    // Updating max and min
    if(root_right->left != NULL) root_right->min = (root_right->left)->min;
    else root_right->min = root_right;

    if(root->right != NULL) root->max = (root->right)->max;
    else root->max = root;
 
    // Updating heights:
    update_node_height_avl_aux(root);
    update_node_height_avl_aux(root_right);

    return root_right; //new root
}
 
//ARRUMAR
type_mMavltree balance_avl_tree_aux(type_mMavltree tree, type_mMavlitems item, type_mMavlptrf_twoitems compare){
    NODE *avl_tree = tree;
    
    // Getting tree balance to check if a previous operation left it unbalanced 
    int balance = get_balance_in_avl_aux(avl_tree);
    if(balance == 1 || balance == 0 || balance == -1){
        printf("não precisa balancear\n");
        return avl_tree; // if not, return.
    } 
 

    // Unbalanced cases:
    if(avl_tree->left != NULL && balance > 1){
        long value_of_comparison_left = (long)compare(item, (avl_tree->left)->item);
        
        // Left Left Case
        if (value_of_comparison_left < 0){
            return right_rotate_subtree_in_avl_tree_aux(avl_tree);
        } 
        // Left Right Case
        if (value_of_comparison_left > 0){
            avl_tree->left =  left_rotate_subtree_in_avl_tree_aux(avl_tree->left);
            balance_avl_tree_aux(avl_tree, ((avl_tree->left)->left)->item, compare);
        }
    } 
    if(avl_tree->right != NULL && balance < -1){
        long value_of_comparison_right = (long)compare(item, (avl_tree->right)->item);
    
        // Right Right Case
        if (value_of_comparison_right > 0){
            return left_rotate_subtree_in_avl_tree_aux(avl_tree);
        }
    
        // Right Left Case
        if (value_of_comparison_right < 0){
            avl_tree->right = right_rotate_subtree_in_avl_tree_aux(avl_tree->right);
            balance_avl_tree_aux(avl_tree, ((avl_tree->right)->right)->item, compare);
        }
    }
 
    return avl_tree;
}

//ARRUMAR
// pq atualizo só do elemento corrente
type_mMavltree insert_item_in_mM_avl_tree(type_mMavltree tree, type_mMavlitems item, type_mMavlptrf_twoitems compare){
    NODE *avl_tree = tree;

    // INSERTING ITEM
    if(avl_tree == NULL){
        return(create_new_node_avl_aux(item));
    }

    long value_of_comparison = (long)compare(item, avl_tree->item);

    // in case item is bigger than avl_tree->item
    if(value_of_comparison > 0){
        printf("fui para a direita\n");
        avl_tree->right = insert_item_in_mM_avl_tree(avl_tree->right, item, compare);
        avl_tree->max = (avl_tree->right)->max; 
    }
    // in case item is smaller than avl_tree->item
    else if(value_of_comparison < 0){
        printf("fui para a esquerda\n");
        avl_tree->left = insert_item_in_mM_avl_tree(avl_tree->left, item, compare);
        avl_tree->min = (avl_tree->left)->min;
    }
    // AQUIDE não to lidando com inserção de elementos repetidos => tecnicamente nao pode ter mesma chave

    // UPDATING HEIGHT (of the current node)
    update_node_height_avl_aux(avl_tree);
    
    
    // BALANCING TREE
    return(balance_avl_tree_aux(avl_tree, item, compare));
}

//ARRUMAR
type_mMavltree delete_item_in_mM_avl_tree(type_mMavltree tree, type_mMavlitems item, type_mMavlptrf_twoitems compare){
    NODE *avl_tree = tree;

    // DELETING ITEM
    if (avl_tree == NULL) return avl_tree;

    long value_of_comparison = (long)compare(item, avl_tree->item);

    // Looking for the item to be deleted
    if(value_of_comparison < 0){
        avl_tree->left = delete_item_in_mM_avl_tree(avl_tree->left, item, compare);
        if(avl_tree->left != NULL) avl_tree->min = (avl_tree->left)->min;
        else avl_tree->min = avl_tree;
    }
    else if(value_of_comparison > 0){
        avl_tree->right = delete_item_in_mM_avl_tree(avl_tree->right, item, compare);
        if(avl_tree->right != NULL) avl_tree->max = (avl_tree->right)->max;
        else avl_tree->max = avl_tree;
    }        
    // Found the item to be deleted.
    else{
        // If node has one or no child
        if((avl_tree->left == NULL) || (avl_tree->right == NULL)){
            if((avl_tree->left == NULL) && (avl_tree->right == NULL)){ // No child
                NODE *temp = avl_tree;
                avl_tree = NULL;
                free(temp);
            }
            else{ 
                if(avl_tree->left){
                    NODE *temp = max_value_in_avl_aux(avl_tree->left);
    
                    avl_tree->item = temp->item; // Copying the data

                    // Delete the inorder successor
                    avl_tree->left = delete_item_in_mM_avl_tree(avl_tree->left, temp->item, compare);
                }

                else{ // avl_tree->right != NULL
                    NODE *temp = min_value_in_avl_aux(avl_tree->right);
    
                    avl_tree->item = temp->item; // Copying the data

                    // Delete the inorder successor
                    avl_tree->right = delete_item_in_mM_avl_tree(avl_tree->right, temp->item, compare);
                }
            }
        }
        // Else: if node has two children
        else {
            // Get the inorder successor (smallest in the right subtree)
            NODE *temp = min_value_in_avl_aux(avl_tree->right);
    
            avl_tree->item = temp->item; // Copying the data

            // Delete the inorder successor
            avl_tree->right = delete_item_in_mM_avl_tree(avl_tree->right, temp->item, compare);
        }
    }
 
    if (avl_tree == NULL) return avl_tree;
 
    // UPDATING HEIGHT (of the current node)
    update_node_height_avl_aux(avl_tree);

    // BALANCING THE AVL TREE
    return(balance_avl_tree_aux(avl_tree, item, compare));
}
 




// protótipos
void traverse_mMavltree_with_conditional_action(type_mMavltree tree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion);
void traverse_mMavltree_with_conditional_action_avlaux(type_mMavltree kdtree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion);
void continue_traverse_avltaux(NODE *tree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion);




// If condition is met, and deletion is set to 1 deletion has to take place
// otherwise loop
void traverse_mMavltree_with_conditional_action(type_mMavltree tree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion){
    if(empty_mM_avl_tree(tree)) return;
    traverse_mMavltree_with_conditional_action_avlaux(tree, traverse_side, condition, action, is_action_deletion);
}

void traverse_mMavltree_with_conditional_action_avlaux(type_mMavltree kdtree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion){
    NODE *tree = kdtree;
    NODE *previous = tree;
    int side;
    
    // Base case:
    if(tree == NULL) return;

    if(tree != NULL){
        if((long)condition(tree->item)){ // até poderia adicionar uma funcao que devolve true or false dependendo se for ter delecao
            if(is_action_deletion){
                tree = action(tree->item);
                if(tree != NULL) traverse_mMavltree_with_conditional_action_avlaux(tree, traverse_side, condition, action, is_action_deletion);
            }
            else{
                action(tree->item);
                continue_traverse_avltaux(tree, traverse_side, condition, action, is_action_deletion);
            } 
        }
        else continue_traverse_avltaux(tree, traverse_side, condition, action, is_action_deletion);
    } 
}

void continue_traverse_avltaux(NODE *tree, type_mMavlptrf_threeitems traverse_side, type_mMavlptrf_oneitem condition, type_mMavlptrf_oneitem action, int is_action_deletion){
    long side = (long)traverse_side(tree->item, (tree->min)->item, (tree->max)->item);

    if(side == 01){ //right
        if(tree->right != NULL) traverse_mMavltree_with_conditional_action_avlaux(tree->right, traverse_side, condition, action, is_action_deletion);
    }
    else if(side == 10){ //left
            if(tree->left != NULL) traverse_mMavltree_with_conditional_action_avlaux(tree->left, traverse_side, condition, action, is_action_deletion);
        }
        else if(side == 11){ //both
                if(tree->right != NULL) traverse_mMavltree_with_conditional_action_avlaux(tree->right, traverse_side, condition, action, is_action_deletion);
                if(tree->left != NULL) traverse_mMavltree_with_conditional_action_avlaux(tree->left, traverse_side, condition, action, is_action_deletion);
            }   
}


// type_mMavltree find_item_in_avl_tree(type_mMavltree tree, type_mMavlitems item){

// }


// type_mMavlitems get_right_child_in_mM_avl_tree(type_mMavlitems item){
// }

// type_mMavlitems get_left_child_in_mM_avl_tree(type_mMavlitems item){
// }






// A debug function AQUIDE
void preorder_debug_fuction_mMavltree(type_mMavltree tree, type_mMavlptrf_oneitem print_item){
    NODE *root = tree;
    if(root != NULL){
        printf("\nheight:%d\n", root->height);
        print_item(root->item);
        printf("\nmax:\t");
        print_item((root->max)->item);
        printf("\nmin:\t");
        print_item((root->min)->item);
        preorder_debug_fuction_mMavltree(root->left, print_item);
        preorder_debug_fuction_mMavltree(root->right, print_item);
    }
}
 
// ANTES O DELETION:
//  if((avl_tree->left == NULL) || (avl_tree->right == NULL)){
//             NODE *temp;
//             if(avl_tree->left) temp = avl_tree->left; // if avl_tree->left != NULL
//             else temp = avl_tree->right;
//             // NODE *temp = avl_tree->left ? avl_tree->left : avl_tree->right; // AQUIDE pode apagar

//             if(temp == NULL){ // No child
//                 temp = avl_tree;
//                 avl_tree = NULL;
//             }
//             else{ 
                
//                 // One child //aqui de 
//                 //como estava antes:
//                 //*avl_tree = *temp; // Copying the contents
//                 //*avl_tree = *temp; // Copying the contents


//             }