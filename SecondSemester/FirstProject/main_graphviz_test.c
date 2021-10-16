#include<stdio.h>
#include<stdlib.h>
#include "graphviz_draw.h"
#include "mM_avl_tree_wlist.h"
#include "rectangle.h"
#include "block.h"

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
// void action_(type_list parent, type_list childleft, type_list childright){
//     printf("action\n");
//     if(parent == NULL) return;
//     set_current_to_first_item_in_list(parent);
//     OBJECT* parent_ = get_current_item_in_list(parent);
//     char idtmp[5];
//     if(draw == 0){
//         sprintf(idtmp, "%d%c", parent_->id, '\0');
//         add_root_in_tree_design(idtmp, output_file);
//         draw++;
//     }

//     if(childleft != NULL){
//         set_current_to_first_item_in_list(childleft);
//         OBJECT* childleft_ = get_current_item_in_list(childleft);

//         appear_node_in_tree_design(output_file);
//         sprintf(idtmp, "%d%c", parent_->id, '\0');
//         add_parent_in_tree_design(idtmp, output_file);
//         sprintf(idtmp, "%d%c", childleft_->id, '\0');
//         add_child_in_tree_design(idtmp, output_file);
//     }
//     else{
//         hide_node_in_tree_design(output_file);
//         sprintf(idtmp, "%d%c", parent_->id, '\0');
//         add_parent_in_tree_design(idtmp, output_file);
//         add_empty_child_in_tree_design(output_file);
//     }

//     if(childright != NULL){
//         set_current_to_first_item_in_list(childright);
//         OBJECT* childright_ = get_current_item_in_list(childright);

//         appear_node_in_tree_design(output_file);
//         sprintf(idtmp, "%d%c", parent_->id, '\0');
//         add_parent_in_tree_design(idtmp, output_file);
//         sprintf(idtmp, "%d%c", childright_->id, '\0');
//         add_child_in_tree_design(idtmp, output_file);
//     }
//     else{
//         hide_node_in_tree_design(output_file);
//         sprintf(idtmp, "%d%c", parent_->id, '\0');
//         add_parent_in_tree_design(idtmp, output_file);
//         add_empty_child_in_tree_design(output_file);
//     }
    
// }


// Cada nó da árvore deve mostrar a coordenada X,
// o número de quadras “dentro” do nó, 
// o cep de algumas (poucas) quadras, 
// o x mínimo, 
// o x máximo 
// e o fator de balanceamento do nó. 
// Opcionalmente: em vez de escrever o fator de balanceamento

type_list global_list;
char* get_info_function(type_list list){
    char* string_final = malloc(sizeof(char) * 200);
    char* string_of_ceps = malloc(sizeof(char) * 120);
    char* string_of_xs = malloc(sizeof(char) * 120);
    set_current_to_first_item_in_list(list);
    type_rect rect = get_current_item_in_list(list);
    double list_x = get_rect_x(rect);
    int number_of_blocks = list_current_size(list);
    long balance;

    char cep[40];
    for(int i=0; i < 3; i++){
        type_rect current_item = get_current_item_in_list(list);
        type_block data = get_rect_data(current_item);
        sprintf(cep, "%s%c", get_block_cep(data), '\0');
        if(i=0) sprintf(string_of_ceps, "%s", cep);
        else sprintf(string_of_ceps, "%s %s", string_of_ceps, cep);

        move_current_forward_in_list(list);
        if(is_current_last_item_in_list(list)) break;
    }
    if(global_list != NULL){
        int done;
        int i;
        set_current_to_first_item_in_list(global_list);
        do{
            done = is_current_last_item_in_list(global_list);

            long list_item = get_current_item_in_list(global_list);
            switch (i) {
            case 0:
                balance = list_item;
                break;
            case 1:
                sprintf(string_of_xs, "left minimum %ld\n", list_item);
                break;
            case 2:
                sprintf(string_of_xs, "%sleft maximum %ld\n", string_of_xs, list_item);
                break;
            case 3:
                sprintf(string_of_xs, "%sright minimum %ld\n", string_of_xs, list_item);
                break;
            case 4:
                sprintf(string_of_xs, "%sright minimum %ld", string_of_xs, list_item);
                break;
            default:
                break;
            }
            i++;

            move_current_forward_in_list(global_list);

        }while(!done);
    }

    sprintf(string_final, "x = %ld\namount of blocks = %d\n%s\n%s\nbalance = %ld", list_x, number_of_blocks, string_of_ceps, string_of_xs, balance);
    free(string_of_ceps);
    free(string_of_xs);
    printf("final string: %s\n", string_final);
    return string_final;
}

void action_(type_list parent, type_list childleft, type_list childright, type_list info_parent, type_list info_lchild, type_list info_rchild){

    void(*getinfo)(type_list);
    getinfo = get_info_function;  

    if(childleft != NULL){
        balance_global = balance_factor_p;
        insert_blocks_rects_parent_list_of_not_null_child(parent, (void*)getinfo);
        balance_global = balance_factor_cl;
        insert_blocks_rects_child_list(childleft, (void*)getinfo); 

    }
    else{
    insert_blocks_rects_parent_list_of_null_child(parent, (void*)getinfo);
    insert_blocks_rects_child_list(childleft, (void*)getinfo); 

    }
    if(childright != NULL){
        balance_global = balance_factor_p;
        insert_blocks_rects_parent_list_of_not_null_child(parent, (void*)getinfo);
        balance_global = balance_factor_cr;
        insert_blocks_rects_child_list(childright, (void*)getinfo); 
    }
    else{
        insert_blocks_rects_parent_list_of_null_child(parent, (void*)getinfo);
        insert_blocks_rects_child_list(childright, (void*)getinfo); 
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
    obj6->id = 20;
    sprintf(obj6->idchar, "rept%c", '\0');


    long(*compare)(OBJECT*, OBJECT*);
    compare = compare_ids;
    void(*print)(OBJECT*);
    print = print_id;

    void(*action)(type_list, type_list, type_list, type_list, type_list, type_list);
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


    traverse_mMlavltree_full_tree_with_action_in_parent_list_and_childs_lists(root, (void*)action, (void*)get_rect_x);
    //traverse_mMlavltree_full_tree_with_action_in_parent_list_and_childs_lists(root, (void*)action);
    //traverse_mMlavltree_with_conditional_action(root, (void*)traverse, (void*)condition, (void*)action);

    end_design(output_file);
}