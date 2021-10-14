#include<stdio.h>
#include<stdlib.h>
#include "graphviz_draw.h"
#include "mM_avl_tree_wlist.h"

int draw = 0;
FILE *output_file;

typedef struct object {
    int id;
    char idchar[10];
    int nivel;
} OBJECT;

void print_id(OBJECT* obj1){
    printf("id: %d\n", obj1->id);
}

// void action_(OBJECT* obj, OBJECT* childleft, OBJECT* childright){
//     printf("action\n");
//     add_parent_in_tree_design(obj->idchar, output_file);
//     add_child_in_tree_design(childleft->idchar, output_file);
//     add_child_in_tree_design(childright->idchar, output_file);
// }


// por enquanto só to inserindo um elemento vou ter que ver como inserir multiplos
void action_(type_list parent, type_list childleft, type_list childright){
    printf("action\n");
    if(parent == NULL) return;
    set_current_to_first_item_in_list(parent);
    OBJECT* parent_ = get_current_item_in_list(parent);
    char idtmp[5];
    if(draw == 0){
        sprintf(idtmp, "%d%c", parent_->id, '\0');
        add_root_in_tree_design(idtmp, output_file);
        draw++;
    }

    if(childleft != NULL){
        set_current_to_first_item_in_list(childleft);
        OBJECT* childleft_ = get_current_item_in_list(childleft);

        appear_node_in_tree_design(output_file);
        sprintf(idtmp, "%d%c", parent_->id, '\0');
        add_parent_in_tree_design(idtmp, output_file);
        sprintf(idtmp, "%d%c", childleft_->id, '\0');
        add_child_in_tree_design(idtmp, output_file);
    }
    else{
        hide_node_in_tree_design(output_file);
        sprintf(idtmp, "%d%c", parent_->id, '\0');
        add_parent_in_tree_design(idtmp, output_file);
        add_empty_child_in_tree_design(output_file);
    }

    if(childright != NULL){
        set_current_to_first_item_in_list(childright);
        OBJECT* childright_ = get_current_item_in_list(childright);

        appear_node_in_tree_design(output_file);
        sprintf(idtmp, "%d%c", parent_->id, '\0');
        add_parent_in_tree_design(idtmp, output_file);
        sprintf(idtmp, "%d%c", childright_->id, '\0');
        add_child_in_tree_design(idtmp, output_file);
    }
    else{
        hide_node_in_tree_design(output_file);
        sprintf(idtmp, "%d%c", parent_->id, '\0');
        add_parent_in_tree_design(idtmp, output_file);
        add_empty_child_in_tree_design(output_file);
    }
    
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


int main(){

    output_file = begin_design("denisedot.dot");
    type_mMlavltree root = create_mMl_avl_tree();
    OBJECT *obj1 = malloc(sizeof(OBJECT));
    obj1->id = 10;
    sprintf(obj1->idchar, "10%c", '\0');
    OBJECT *obj2 = malloc(sizeof(OBJECT));
    obj2->id = 20;
    sprintf(obj2->idchar, "20%c", '\0');
    OBJECT *obj3 = malloc(sizeof(OBJECT));
    obj3->id = 30;
    sprintf(obj3->idchar, "30%c", '\0');
    OBJECT *obj4 = malloc(sizeof(OBJECT));
    obj4->id = 40;
    sprintf(obj4->idchar, "40%c", '\0');
    OBJECT *obj5 = malloc(sizeof(OBJECT));
    obj5->id = 50;
    sprintf(obj5->idchar, "50%c", '\0');
    OBJECT *obj6 = malloc(sizeof(OBJECT));
    obj6->id = 25;
    sprintf(obj6->idchar, "25%c", '\0');


    long(*compare)(OBJECT*, OBJECT*);
    compare = compare_ids;
    void(*print)(OBJECT*);
    print = print_id;

    void(*action)(type_list, type_list, type_list);
    action = action_;  


    root = insert_item_in_mMl_avl_tree(root, obj1, (void*)compare);
    printf("Preorder traversal of the constructed AVL"
        " tree is \n");
    preorder_debug_fuction_mMlavltree(root, (void*)print);
    root = insert_item_in_mMl_avl_tree(root, obj2, (void*)compare);
        printf("Preorder traversal of the constructed AVL"
        " tree is \n");
    preorder_debug_fuction_mMlavltree(root, (void*)print);
    root = insert_item_in_mMl_avl_tree(root, obj3, (void*)compare);
        printf("Preorder traversal of the constructed AVL"
        " tree is \n");
    preorder_debug_fuction_mMlavltree(root, (void*)print);
    root = insert_item_in_mMl_avl_tree(root, obj4, (void*)compare);
     printf("Preorder traversal of the constructed AVL"
        " tree is \n");
    preorder_debug_fuction_mMlavltree(root, (void*)print);
    root = insert_item_in_mMl_avl_tree(root, obj5, (void*)compare);
        printf("Preorder traversal of the constructed AVL"
        " tree is \n");
    preorder_debug_fuction_mMlavltree(root, (void*)print);
    root = insert_item_in_mMl_avl_tree(root, obj6, (void*)compare);


    printf("Preorder traversal of the constructed AVL"
        " tree is \n");
    preorder_debug_fuction_mMlavltree(root, (void*)print);

    traverse_mMlavltree_full_tree_with_action_in_parent_list_and_childs_lists(root, (void*)action);
    //traverse_mMlavltree_with_conditional_action(root, (void*)traverse, (void*)condition, (void*)action);

    end_design(output_file);
}