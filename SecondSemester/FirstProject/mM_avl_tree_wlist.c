//
//  mM_avl_tree_wlist.c
//  
//
//  Created by Denise F. de Rezende on 12/08/21.
//

#include<stdio.h>
#include<stdlib.h>
#include "mM_avl_tree_wlist.h"

typedef struct avl_tree_node {
    type_mMlavlitems* list;
    int height;
    struct avl_tree_node *left; // left child
    struct avl_tree_node *right; // right child
    struct avl_tree_node *lmax; // max do filho esquerdo 
    struct avl_tree_node *lmin; // min do filho direito
    struct avl_tree_node *rmax; // max do filho esquerdo 
    struct avl_tree_node *rmin; // min do filho direito
} NODE;

type_mMlavltree create_mMl_avl_tree(){
    return NULL;
}

type_mMlavltree create_new_node_avl_aux(type_mMlavlitems item){
    NODE *temp = malloc(sizeof(NODE));
    type_list list = create_list();
    insert_item_at_the_end_of_list(list, item);
    temp->list = list;
    temp->height = 1;
    temp->left = NULL;
    temp->right = NULL;
    temp->lmax = temp;
    temp->lmin = temp;
    temp->rmax = temp;
    temp->rmin = temp;
    return temp;
}

int empty_mMl_avl_tree(type_mMlavltree tree){
    NODE *avl_tree = tree;
    return(avl_tree == NULL);
}

int maximum_two_int_avl_aux(int a, int b){
    if(a > b) return a;
    else return b;
}

int node_height_avl_aux(type_mMlavltree tree){
    NODE *avl_tree = tree;
    if(avl_tree == NULL) return 0;
    return(avl_tree->height);
}

/* Returns the minimum value item in the tree. 
   Note that: the entire tree is not searched. */
type_mMlavltree min_value_in_avl_aux(NODE* node){
    NODE* current = node;
 
    // loop down to find the leftmost leaf, which is equivalent to the minimum value
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

/* Returns the maximum value item in the tree. 
   Note that: the entire tree is not searched. */
type_mMlavltree max_value_in_avl_aux(NODE* node){
    NODE* current = node;
 
    // loop down to find the rightmost leaf, which is equivalent to the maximum value
    while (current->right != NULL)
        current = current->right;
 
    return current;
}

/* Returns the difference between the left and right height of the tree root given.
    Note that the calculation is: left height - right height.*/
int get_balance_in_avl_aux(type_mMlavltree tree){
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
 
    // Updating max and min of both left and right subtree
    // New root update
    if(root_left->right != NULL) root_left->rmax = (root_left->right)->rmax;
    else root_left->rmax = root_left;
    // Old root update
    if(root->left != NULL) root->lmin = (root->left)->lmin;
    else root->lmin = root; 
    // New root update
    if(root_left->right != NULL) root_left->rmin = (root_left->right)->lmin;
    else root_left->rmin = root_left;
    // Old root update
    if(root->left != NULL) root->lmax = (root->left)->rmax;
    else root->lmax = root; 
    
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

    // Updating max and min of both left and right subtree
    // New root update
    if(root_right->left != NULL) root_right->lmin = (root_right->left)->lmin;
    else root_right->lmin = root_right;
    // Old root update
    if(root->right != NULL) root->rmax = (root->right)->rmax;
    else root->rmax = root;
    // New root update
    if(root_right->left != NULL) root_right->lmax = (root_right->left)->rmax;
    else root_right->lmax = root_right;
    // Old root update
    if(root->right != NULL) root->rmin = (root->right)->lmin;
    else root->rmin = root;

    // Updating heights:
    update_node_height_avl_aux(root);
    update_node_height_avl_aux(root_right);

    return root_right; //new root
}
 

//ARRUMAR
type_mMlavltree balance_avl_tree_aux(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare){
    NODE *avl_tree = tree;
    
    // Getting tree balance to check if a previous operation left it unbalanced 
    int balance = get_balance_in_avl_aux(avl_tree);
    if(balance == 1 || balance == 0 || balance == -1){
        return avl_tree; // if not, return.
    } 
 

    // Unbalanced cases:
    if(avl_tree->left != NULL && balance > 1){
        set_current_to_first_item_in_list((avl_tree->left)->list);
        type_litems current_item = get_current_item_in_list((avl_tree->left)->list);
        long value_of_comparison_left = (long)compare(item, current_item);
        
        // Left Left Case
        if (value_of_comparison_left < 0){
            return right_rotate_subtree_in_avl_tree_aux(avl_tree);
        } 
        // Left Right Case
        if (value_of_comparison_left > 0){
            avl_tree->left =  left_rotate_subtree_in_avl_tree_aux(avl_tree->left);
            set_current_to_first_item_in_list(((avl_tree->left)->left)->list);
            type_litems current_item = get_current_item_in_list(((avl_tree->left)->left)->list);
            balance_avl_tree_aux(avl_tree, current_item, compare);
        }
    } 
    if(avl_tree->right != NULL && balance < -1){
        set_current_to_first_item_in_list((avl_tree->right)->list);
        type_litems current_item = get_current_item_in_list((avl_tree->right)->list);
        long value_of_comparison_right = (long)compare(item, current_item);
    
        // Right Right Case
        if (value_of_comparison_right > 0){
            return left_rotate_subtree_in_avl_tree_aux(avl_tree);
        }
    
        // Right Left Case
        if (value_of_comparison_right < 0){
            avl_tree->right = right_rotate_subtree_in_avl_tree_aux(avl_tree->right);
            set_current_to_first_item_in_list(((avl_tree->right)->right)->list);
            type_litems current_item = get_current_item_in_list(((avl_tree->right)->right)->list);
            balance_avl_tree_aux(avl_tree, current_item, compare);
        }
    }
 
    return avl_tree;
}

//ARRUMAR
// pq atualizo só do elemento corrente
type_mMlavltree insert_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare){
    NODE *avl_tree = tree;

    // INSERTING ITEM
    if(avl_tree == NULL){
        return(create_new_node_avl_aux(item));
    }

    set_current_to_first_item_in_list(avl_tree->list);
    type_litems current_item = get_current_item_in_list(avl_tree->list);
    long value_of_comparison = (long)compare(item, current_item);

    // in case item is bigger than current_item
    //SOS
    if(value_of_comparison > 0){
        avl_tree->right = insert_item_in_mMl_avl_tree(avl_tree->right, item, compare);
        avl_tree->rmax = (avl_tree->right)->rmax; 
        avl_tree->rmin = (avl_tree->right)->lmin;
    }
    // in case item is smaller than current_item
    else if(value_of_comparison < 0){
        avl_tree->left = insert_item_in_mMl_avl_tree(avl_tree->left, item, compare);
        avl_tree->lmin = (avl_tree->left)->lmin;
        avl_tree->lmax = (avl_tree->left)->rmax;
    }
    // AQUIDE não to lidando com inserção de elementos repetidos => tecnicamente nao pode ter mesma chave

    // UPDATING HEIGHT (of the current node)
    update_node_height_avl_aux(avl_tree);
    
    
    // BALANCING TREE
    return(balance_avl_tree_aux(avl_tree, item, compare));
}

type_mMlavltree delete_item_in_mMl_avl_tree(type_mMlavltree tree, type_mMlavlitems item, type_mMlavlptrf_twoitems compare){
    NODE *avl_tree = tree;

    // DELETING ITEM
    if (avl_tree == NULL) return avl_tree;

    set_current_to_first_item_in_list(avl_tree->list);
    type_litems current_item = get_current_item_in_list(avl_tree->list);
    long value_of_comparison = (long)compare(item, current_item);

    // Looking for the item to be deleted
    if(value_of_comparison < 0){
        avl_tree->left = delete_item_in_mMl_avl_tree(avl_tree->left, item, compare);
        if(avl_tree->left == NULL){
            avl_tree->lmin = avl_tree;
            avl_tree->lmax = avl_tree;
        }
        else{
            avl_tree->lmin = (avl_tree->left)->lmin;
            avl_tree->lmax = (avl_tree->left)->rmax;
        }
    }
    else if(value_of_comparison > 0){
        avl_tree->right = delete_item_in_mMl_avl_tree(avl_tree->right, item, compare);
        if(avl_tree->right == NULL){
            avl_tree->rmin = avl_tree;
            avl_tree->rmax = avl_tree;
        }
        else{
            avl_tree->rmax = (avl_tree->right)->rmax; 
            avl_tree->rmin = (avl_tree->right)->lmin;
        }
    }        
    // Found the list that contains the item to be deleted.
    else{
        // deleting item from list
        delete_item_in_list(avl_tree->list, item, compare);
        // If list is not empty => dont update anything (everything is right)
        if(!empty_list(avl_tree->list)){
            return avl_tree;
        }
        // else delete list and delete node

        destroi_list(avl_tree->list);

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
    
                    avl_tree->list = temp->list; // Copying the data

                    // Delete the inorder successor
                    avl_tree->left = delete_item_in_mMl_avl_tree(avl_tree->left, temp->list, compare);
                }

                else{ // avl_tree->right != NULL
                    NODE *temp = min_value_in_avl_aux(avl_tree->right); //AQUI DE, poderia só pegar do filho?
    
                    avl_tree->list = temp->list; // Copying the data

                    // Delete the inorder successor
                    avl_tree->right = delete_item_in_mMl_avl_tree(avl_tree->right, temp->list, compare);
                }
            }
        }
        // Else: if node has two children
        else {
            // Get the inorder successor (smallest in the right subtree)
            NODE *temp = min_value_in_avl_aux(avl_tree->right);
    
            avl_tree->list = temp->list; // Copying the data

            // Delete the inorder successor
            avl_tree->right = delete_item_in_mMl_avl_tree(avl_tree->right, temp->list, compare);
        }
    }
 
    if (avl_tree == NULL) return avl_tree;
 
    // UPDATING HEIGHT (of the current node)
    update_node_height_avl_aux(avl_tree);

    // BALANCING THE AVL TREE
    return(balance_avl_tree_aux(avl_tree, item, compare));
}
 




// protótipos
void traverse_mMlavltree_with_conditional_action(type_mMlavltree tree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action);
void traverse_mMlavltree_with_conditional_action_avlaux(type_mMlavltree avltree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action);
void continue_traverse_avltaux(NODE *tree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action);




// If condition is met, and deletion is set to 1 deletion has to take place
// otherwise loop
void traverse_mMlavltree_with_conditional_action(type_mMlavltree tree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action){
    if(empty_mMl_avl_tree(tree)) return;
    traverse_mMlavltree_with_conditional_action_avlaux(tree, traverse_side, condition, action);
}

void traverse_mMlavltree_with_conditional_action_avlaux(type_mMlavltree avltree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action){
    NODE *tree = avltree;
    NODE *previous = tree;
    int side;
    
    // Base case:
    if(tree == NULL) return;

    if(tree != NULL){
        set_current_to_first_item_in_list(tree->list);
        type_litems min_item = get_current_item_in_list(tree->list);
        int done;
        do{
            done = is_current_last_item_in_list(tree->list);
            type_litems item = get_current_item_in_list(tree->list);
            if((long)condition(item)){
                action(item);
            }
            printf("done = %d\n", done);
        }while(!done);

        continue_traverse_avltaux(tree, traverse_side, condition, action);
    }
}

void continue_traverse_avltaux(NODE *tree, type_mMlavlptrf_fiveitems traverse_side, type_mMlavlptrf_oneitem condition, type_mMlavlptrf_oneitem action){
    printf("continue_traverse_avltaux\n");
    set_current_to_first_item_in_list(tree->list);
    type_litems current_item = get_current_item_in_list(tree->list);
    printf("current_item\n");
    //verificar se current == null???
    
    printf("(tree->lmin) == NULL ? %d\n", (tree->lmin) == NULL);
    printf("(tree->lmin)->list == NULL ? %d\n", (tree->lmin)->list == NULL);
    set_current_to_first_item_in_list((tree->lmin)->list);
    type_litems lmin_item = get_current_item_in_list((tree->lmin)->list);
    printf("lmin_item\n");

    set_current_to_first_item_in_list((tree->lmax)->list);
    type_litems lmax_item = get_current_item_in_list((tree->lmax)->list);
    printf("lmax_item\n");

    set_current_to_first_item_in_list((tree->rmin)->list);
    type_litems rmin_item = get_current_item_in_list((tree->rmin)->list);
    printf("lmax_item\n");

    set_current_to_first_item_in_list((tree->rmax)->list);
    type_litems rmax_item = get_current_item_in_list((tree->rmax)->list);
    printf("rmax_item\n");

    printf("continue_traverse_avltaux indo mandar pro trvaerse\n");

    long side = (long)traverse_side(current_item, lmin_item, lmax_item, rmin_item, rmax_item);

    if(side == 01){ //right
        if(tree->right != NULL) traverse_mMlavltree_with_conditional_action_avlaux(tree->right, traverse_side, condition, action);
    }
    else if(side == 10){ //left
            if(tree->left != NULL) traverse_mMlavltree_with_conditional_action_avlaux(tree->left, traverse_side, condition, action);
        }
        else if(side == 11){ //both
                if(tree->right != NULL) traverse_mMlavltree_with_conditional_action_avlaux(tree->right, traverse_side, condition, action);
                if(tree->left != NULL) traverse_mMlavltree_with_conditional_action_avlaux(tree->left, traverse_side, condition, action);
            }   
}

// A debug function AQUIDE
void preorder_debug_fuction_mMlavltree(type_mMlavltree tree, type_mMlavlptrf_oneitem print_item){
    NODE *root = tree;
    if(root != NULL){
        // PRINTING HEIGHT
        printf("\nheight:%d\n", root->height);
        set_current_to_first_item_in_list(root->list);
        int done;
        do{
            // PRINTING ITEMS IN LIST
            done = is_current_last_item_in_list(root->list);
            type_litems current_item = get_current_item_in_list(root->list);
            print_item(current_item);
        }while(!done);

        // PRINTING SUBTREE MAX
        printf("\nLEFT:\t");
        set_current_to_first_item_in_list((root->lmax)->list);
        type_litems max_item = get_current_item_in_list((root->lmax)->list);
        printf("\nmax:\t");
        print_item(max_item);
        // PRINTING SUBTREE MIN
        set_current_to_first_item_in_list((root->lmin)->list);
        type_litems min_item = get_current_item_in_list((root->lmin)->list);
        printf("\nmin:\t");
        print_item(min_item);


        // PRINTING SUBTREE MAX
        printf("\nRIGHT:\t");
        set_current_to_first_item_in_list((root->rmax)->list);
        max_item = get_current_item_in_list((root->rmax)->list);
        printf("\nmax:\t");
        print_item(max_item);
        // PRINTING SUBTREE MIN
        set_current_to_first_item_in_list((root->rmin)->list);
        min_item = get_current_item_in_list((root->rmin)->list);
        printf("\nmin:\t");
        print_item(min_item);

        preorder_debug_fuction_mMlavltree(root->left, print_item);
        preorder_debug_fuction_mMlavltree(root->right, print_item);
    }
}
 