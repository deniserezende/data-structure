#include<stdio.h>
#include<stdlib.h>
#include "graphviz_draw.h"
#include "mM_avl_tree_wlist.h"

FILE *output_file;

typedef struct object {
    int id;
    int nivel;
} OBJECT;

void print_id(OBJECT* obj1){
    printf("id: %d\n", obj1->id);
}

void print_design(OBJECT* obj){

    if(obj == NULL) return;
    printf("cheguei no print_desing\n");
    //erro ta aqui pq eu to mandando um obj e nao um node ai ele nao acessa os ponteiros para devolver os filhos
    OBJECT *rchild = get_right_child_in_avl_tree(obj);
    OBJECT *lchild = get_left_child_in_avl_tree(obj);
    printf("peguei os objs\n");

    printf("lchild == NULL?%d\n", lchild == NULL);
    printf("rchild == NULL?%d\n", rchild == NULL);


    char idparent[10];
    char idlchild[10];
    char idrchild[10];
    sprintf(idparent, "%d", obj->id);
    printf("parent = %d\n", obj->id);
    printf("parent done\n");
    printf("lchild = %d\n", lchild->id);
    if(lchild != NULL ){ 
        sprintf(idlchild, "%d", lchild->id);
    }
    if(rchild != NULL){
        sprintf(idrchild, "%d", rchild->id);
    }



    printf("saindo no print_desing\n");
    if(lchild == NULL || rchild == NULL){ 
        if(lchild == NULL && rchild == NULL){
            add_tree_element(idparent, NULL, NULL, output_file);
        }
        else{
            if(lchild == NULL){
                add_tree_element(idparent, NULL, idrchild, output_file);
            }
            else{
                add_tree_element(idparent, idlchild, NULL, output_file);
            }
        }
        
    }
    else add_tree_element(idparent, idlchild, idrchild, output_file);
}

long compare_ids(OBJECT* obj1, OBJECT* obj2){
    if (obj1->id > obj2->id){
        return (long)1;
    }
    else if (obj1->id < obj2->id){
        return (long)-1;
    }
    else{
        return 0;
    }
}

long traverse_side(OBJECT* obj){
    return 11;
}

long condition_true(OBJECT* obj){
    return 1;
}


/* Driver program to test above function*/
int main(){
    type_avltree root = create_avl_tree();
 
  /* Constructing tree given in the above figure */
    OBJECT *obj1 = malloc(sizeof(OBJECT));
    obj1->id = 10;
    OBJECT *obj2 = malloc(sizeof(OBJECT));
    obj2->id = 20;
    OBJECT *obj3 = malloc(sizeof(OBJECT));
    obj3->id = 30;
    OBJECT *obj4 = malloc(sizeof(OBJECT));
    obj4->id = 40;
    OBJECT *obj5 = malloc(sizeof(OBJECT));
    obj5->id = 50;
    OBJECT *obj6 = malloc(sizeof(OBJECT));
    obj6->id = 25;


    long(*compare)(OBJECT*, OBJECT*);
    compare = compare_ids;


    void(*print)(OBJECT*);
    print = print_id;

    long(*ptr_traverse_side)(OBJECT*);
    ptr_traverse_side = traverse_side;

    long(*ptr_condition_true)(OBJECT*);
    ptr_condition_true = condition_true;


    void(*ptr_action)(OBJECT*);
    ptr_action = print_design;

    root = insert_item_in_avl_tree(root, obj1, (void*)compare);
    root = insert_item_in_avl_tree(root, obj2, (void*)compare);
    root = insert_item_in_avl_tree(root, obj3, (void*)compare);
    root = insert_item_in_avl_tree(root, obj4, (void*)compare);
    root = insert_item_in_avl_tree(root, obj5, (void*)compare);
    root = insert_item_in_avl_tree(root, obj6, (void*)compare);


        printf("Preorder traversal of the constructed AVL"
            " tree is \n");
    preorder_debug_fuction(root, (void*)print);

    output_file = begin_design("denisetemp.txt");
    printf("criou output\n");
    traverse_avltree_with_conditional_action(root, (void*)ptr_traverse_side, (void*)ptr_condition_true, (void*)ptr_action, 0);
    printf("inseriu elementos\n");
    end_design(output_file);
    printf("fechou output\n");

    root = delete_item_in_avl_tree(root, obj4, (void*)compare);
    root = delete_item_in_avl_tree(root, obj5, (void*)compare);

    printf("Preorder traversal of the constructed AVL"
            " tree is \n");
    preorder_debug_fuction(root, (void*)print);

    free(obj1);
    free(obj2);
    free(obj3);
    free(obj4);    
    free(obj5);
    free(obj6);
    return 0;
}