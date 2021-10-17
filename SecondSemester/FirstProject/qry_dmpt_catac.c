#include "qry_dmpt_catac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

type_svg QDC_SVGFILE;
type_txt QDC_TXTFILE;
type_dot QDC_DOTFILE;

type_hashtable QDC_property_leases, QDC_properties_table, QDC_blocks_table, QDC_people_table;
type_mMlavltree QDC_blocks_avl;
double QDC_x1, QDC_y1, QDC_h, QDC_w;
char QDC_ID[40];
type_list QDC_blocks_to_delete;

#define QDC_SIZE_DOUBLESTR 10

void _QDC_report_property_txt_(type_property property){
    char *cardinal_direction = malloc(sizeof(char)*3);
    sprintf(cardinal_direction, "%c%c", get_property_cardinal_direction(property), '\0');
    insert_string_in_txt(QDC_TXTFILE, get_property_cep(property));
    insert_string_in_txt(QDC_TXTFILE, cardinal_direction);
    char *number = malloc(sizeof(char) * 7);
    sprintf(number, "%d%c", get_property_house_number(property), '\0');
    insert_string_in_txt(QDC_TXTFILE, number);
    insert_string_in_txt(QDC_TXTFILE, get_property_additional_address_data(property));

    free(cardinal_direction);
    free(number);
}

void _QDC_report_property_lease_txt_(type_property property){
    insert_string_in_txt(QDC_TXTFILE, get_property_lease_id(property));
    _QDC_report_property_txt_(property);
    
    char *area = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(area, "%.2lf%c", get_property_area(property), '\0');
    insert_string_in_txt(QDC_TXTFILE, area);

    char *monthly_rent = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(monthly_rent, "%.2lf%c", get_property_monthly_rent(property), '\0');
    insert_string_in_txt(QDC_TXTFILE, monthly_rent);

    free(area);
    free(monthly_rent);
}

void _QDC_report_person_txt_(type_person person){
    char *gender = malloc(sizeof(char)*3);
    char *name = get_person_full_name(person);
    sprintf(gender, "%c%c", get_person_gender(person), '\0');
    insert_string_in_txt(QDC_TXTFILE, get_person_cpf(person));
    insert_string_in_txt(QDC_TXTFILE, name);
    insert_string_in_txt(QDC_TXTFILE, gender);
    insert_string_in_txt(QDC_TXTFILE, get_person_birthday(person));
    free(name);
    free(gender);
}

void _QDC_report_block_txt_(type_rect block_rect){
    type_block block_data = get_rect_data(block_rect);
    insert_string_in_txt(QDC_TXTFILE, get_block_cep(block_data));

    char *x_string = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(x_string, "%.2lf%c", get_rect_x(block_rect), '\0');
    insert_string_in_txt(QDC_TXTFILE, x_string);

    char *y_string = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(y_string, "%.2lf%c", get_rect_y(block_rect), '\0');
    insert_string_in_txt(QDC_TXTFILE, y_string);

    char *w_string = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(w_string, "%.2lf%c", get_rect_width(block_rect), '\0');
    insert_string_in_txt(QDC_TXTFILE, w_string);

    char *h_string = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(h_string, "%.2lf%c", get_rect_height(block_rect), '\0');
    insert_string_in_txt(QDC_TXTFILE, h_string);
}


void action_property_catac_(type_hashitem property){
    type_person owner = get_property_owner(property);
    if(owner != NULL){
        _QDC_report_person_txt_(owner);
        remove_owned_property_from_person(owner, 0);
        set_id(get_person_cpf(owner));
        type_hashitem del_owner = delete_item_in_hash_table(QDC_people_table, get_person_formatted_cpf(owner), (void*)get_person_formatted_cpf, (void*)verify_person_found);
        remove_person(del_owner);
    }
    _QDC_report_property_txt_(property);
    set_id(get_property_cep(property));
    type_property del_property = delete_item_in_hash_table(QDC_properties_table, get_property_cep_key(property), (void*)get_property_cep_key, (void*)verify_property_found);
    remove_property(del_property);
}

void deallocate_property_catac_(type_hashitem property){
    type_person owner = get_property_owner(property);
    if(owner != NULL){
        _QDC_report_person_txt_(owner);
        remove_owned_property_from_person(owner, 0);
        set_id(get_person_cpf(owner));
        type_hashitem del_owner = delete_item_in_hash_table(QDC_people_table, get_person_formatted_cpf(owner), (void*)get_person_formatted_cpf, (void*)verify_person_found);
        remove_person(del_owner);
    }
    _QDC_report_property_txt_(property);
    set_id(get_property_cep(property));
    remove_property(property);
}

long condition_property_lease_catac_(type_property property_lease){
    if(strcmp(get_property_cep(property_lease), QDC_ID) == 0){
        return 1;
    }
    return 0;
}

void action_property_lease_catac_(type_hashitem property_lease){
    int rent_status = get_property_rent_status(property_lease);
        // If it's not for rent then there is a tenant
        if(rent_status == 0){
            type_person tenant = get_property_tenant(property_lease);
            if(tenant != NULL){
                _QDC_report_person_txt_(tenant);
                remove_rented_property_from_person(tenant, 0);

                set_id(get_person_cpf(tenant));
                type_hashitem del_tenant = delete_item_in_hash_table(QDC_people_table, get_person_formatted_cpf(tenant), (void*)get_person_formatted_cpf, (void*)verify_person_found);
                remove_person(del_tenant);
            }
        }
    _QDC_report_property_txt_(property_lease);
    set_id(get_property_cep(property_lease));
    type_property del_property = delete_item_in_hash_table(QDC_properties_table, get_property_cep_key(property_lease), (void*)get_property_cep_key, (void*)verify_property_leases);
    remove_property(del_property);
}

void deallocate_property_lease_catac_(type_hashitem property_lease){
    int rent_status = get_property_rent_status(property_lease);
    // If it's not for rent then there is a tenant
    if(rent_status == 0){
        type_person tenant = get_property_tenant(property_lease);
        if(tenant != NULL){
            _QDC_report_person_txt_(tenant);
            remove_rented_property_from_person(tenant, 0);

            set_id(get_person_cpf(tenant));
            type_hashitem del_tenant = delete_item_in_hash_table(QDC_people_table, get_person_formatted_cpf(tenant), (void*)get_person_formatted_cpf, (void*)verify_person_found);
            remove_person(del_tenant);
        }
    }
    _QDC_report_property_txt_(property_lease);
    set_id(get_property_cep(property_lease));
    remove_property(property_lease);
}

void _catac_svg(type_mMlavlitems block_rect){
    insert_rectangle_with_different_opacity_in_svg(QDC_SVGFILE, get_rect_x(block_rect), get_rect_y(block_rect), get_rect_width(block_rect), get_rect_height(block_rect), "#AB37C8", "#AA0044", 0.5, 2);
}


void action_catac(type_mMlavlitems block_rect){
    type_block block = get_rect_data(block_rect);
    long cep_key = get_block_formatted_cep(block);
    char *cep = get_block_cep(block);

    void(*action_property_ptr)(type_property);
    action_property_ptr = action_property_catac_;

    void(*deallocate_property_ptr)(type_property);
    deallocate_property_ptr = deallocate_property_catac_;

    void(*deallocate_property_lease_ptr)(type_property);
    deallocate_property_lease_ptr = deallocate_property_lease_catac_;

    void(*action_property_lease_ptr)(type_property);
    action_property_lease_ptr = action_property_lease_catac_;

    long(*condition_property_lease_ptr)(type_property);
    condition_property_lease_ptr = condition_property_lease_catac_;
    
    QDC_x1 = get_rect_x(block_rect);
    QDC_y1 = get_rect_y(block_rect);
    QDC_h = get_rect_height(block_rect); 
    QDC_w = get_rect_width(block_rect);

    set_id(cep);
    traverse_hash_table_with_conditional_deletion_optimal(QDC_properties_table, cep_key, (void*)verify_property_found, (void*)deallocate_property_ptr);
    //traverse_hash_table_with_conditional_action_optimal(QDC_properties_table, cep_key, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_property_ptr);
    
    sprintf(QDC_ID, "%s%c", cep, '\0');
    traverse_full_hash_table_with_conditional_deletion(QDC_property_leases, (void*)condition_property_lease_ptr, (void*)deallocate_property_lease_ptr);
    //traverse_full_hash_table_with_conditional_action(QDC_property_leases, (void*)condition_property_lease_ptr, (void*)action_property_lease_ptr);
    //traverse_hash_table_with_conditional_action_optimal(QDC_property_leases, cep, (void*)get_property_cep_key, (void*)verify_property_leases, (void*)action_property_lease_ptr);

    set_id(cep);
    type_rect block_rect_del = delete_item_in_hash_table(QDC_blocks_table, get_key_from_block(block_rect), (void*)get_key_from_block, (void*)verify_block_found);
    insert_item_at_the_end_of_list(QDC_blocks_to_delete, block_rect_del);

    //type_mMlavltree block_avl = delete_item_in_mMl_avl_tree(QDC_blocks_avl, block_rect_del, (void*)compare_rectangles_by_x_coordinate);
    _QDC_report_block_txt_(block_rect_del);
    _catac_svg(block_rect_del);
    // type_block block_data = get_rect_data(block_rect_del);
    // remove_block(block_data);
    // destroi_rectangle(block_rect_del);

    return;
}

type_mMlavltree delete_blocks_from_blocks_avl(type_mMlavltree blocks_avl, type_list list_of_blocks){
    int done;
    type_rect rect;
    type_block block_data;
    if(empty_list(list_of_blocks)){
        destroi_list(list_of_blocks);
        return blocks_avl;
    }
    set_current_to_first_item_in_list(list_of_blocks);
    int i = 0;
    do{
        i++;
        done = is_current_last_item_in_list(list_of_blocks);
        rect = get_current_item_in_list(list_of_blocks);
        set_id(get_property_cep(get_rect_data(rect)));
        blocks_avl = delete_item_in_mMl_avl_tree(blocks_avl, rect, (void*)compare_rectangles_by_x_coordinate, (void*)compare_rect_blocks_cep);
        block_data = get_rect_data(rect);
        remove_block(block_data);
        destroi_rectangle(rect);
        //delete_current_item_in_list(list_of_blocks);
        move_current_forward_in_list(list_of_blocks);
    }while(!done);
    destroi_list(list_of_blocks);
    return blocks_avl;
}

// Remover as quadras, moradores que estejam inteiramente contidas na região delimitada pelo retângulo x,y,w,h. 
// Ofertas de locação dentro da região também deve ser removidas.
// TXT: imprimir identificadores e dados associados a tudo o que foi removido.
// SVG: elementos removidos não devem aparecer. 
// Desenhar sob o mapa o referido retângulo com cor de preenchimento #AB37C8, 
// cor de borda #AA0044 e com 50% de transparência.
type_mMlavltree catac(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable property_leases, type_hashtable people_table, double x, double y, double w, double h){

    QDC_SVGFILE = SVGFILE;
    QDC_TXTFILE = TXTFILE;

    QDC_property_leases = property_leases;
    QDC_properties_table = properties_table;
    QDC_blocks_avl = blocks_avl;
    QDC_blocks_table = blocks_table;
    QDC_people_table = people_table;
    QDC_blocks_to_delete = create_list();

    void(*action_ptr)(type_mMlavlitems);
    action_ptr = action_catac;
    set_x1_x2_y1_y2(x, x+w, y, y+h);
    traverse_mMlavltree_with_conditional_action(blocks_avl, (void*)traverse_side_rect_in_rect_, (void*)condition_rect_in_rect_, (void*)action_ptr);    

    blocks_avl = delete_blocks_from_blocks_avl(blocks_avl, QDC_blocks_to_delete);
    return blocks_avl;
}












type_list QDC_list;
char* get_info_for_dot_catac(type_list list){
    char* string_final = malloc(sizeof(char) * 200);
    char* string_of_ceps = malloc(sizeof(char) * 120);
    char* string_of_xs = malloc(sizeof(char) * 120);
    set_current_to_first_item_in_list(list);
    type_rect rect = get_current_item_in_list(list);
    double list_x = get_rect_x(rect);
    int number_of_blocks = list_current_size(list);
    long balance = 0;

    char cep[40];
    for(int i=0; i < 3; i++){
        type_rect current_item = get_current_item_in_list(list);
        type_block data = get_rect_data(current_item);
        sprintf(cep, "%s%c", get_block_cep(data), '\0');
        if(i==0) sprintf(string_of_ceps, "%s", cep);
        else sprintf(string_of_ceps, "%s %s", string_of_ceps, cep);

        move_current_forward_in_list(list);
        if(is_current_last_item_in_list(list)) break;
    }
    sprintf(string_of_xs, "%c", '\0');
    if(QDC_list != NULL){
        int done;
        int i = 0;
        set_current_to_first_item_in_list(QDC_list);
        do{
            done = is_current_last_item_in_list(QDC_list);

            long list_item = (long)get_current_item_in_list(QDC_list);
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

            move_current_forward_in_list(QDC_list);

        }while(!done);
    }

    sprintf(string_final, "\"x = %f \n amount of blocks = %d \n %s \n %s \n balance = %ld\"", list_x, number_of_blocks, string_of_ceps, string_of_xs, balance);
    free(string_of_ceps);
    free(string_of_xs);
    //printf("final string: \n%s\n", string_final);
    return string_final;
}

void action_dot_dmpt_(type_list parent, type_list childleft, type_list childright, type_list info_parent, type_list info_lchild, type_list info_rchild){

    char*(*getinfo)(type_list);
    getinfo = get_info_for_dot_catac;  

    if(childleft != NULL){
        QDC_list = info_parent;
        insert_blocks_rects_parent_list_of_not_null_child(QDC_DOTFILE, parent, (void*)getinfo);
        QDC_list = info_lchild;
        insert_blocks_rects_child_list(QDC_DOTFILE, childleft, (void*)getinfo); 

    }
    else{
        QDC_list = info_parent;
        insert_blocks_rects_parent_list_of_null_child(QDC_DOTFILE, parent, (void*)getinfo);
        insert_blocks_rects_child_list(QDC_DOTFILE, childleft, (void*)getinfo); 
    }
    if(childright != NULL){
        QDC_list = info_parent;
        insert_blocks_rects_parent_list_of_not_null_child(QDC_DOTFILE, parent, (void*)getinfo);
        QDC_list = info_rchild;
        insert_blocks_rects_child_list(QDC_DOTFILE, childright, (void*)getinfo); 
    }
    else{
        QDC_list = info_parent;
        insert_blocks_rects_parent_list_of_null_child(QDC_DOTFILE, parent, (void*)getinfo);
        insert_blocks_rects_child_list(QDC_DOTFILE, childright, (void*)getinfo); 
    }
}

// Imprime o estado atual da árvore no arquivo <arq>-sfx.dot.
// Cada nó da árvore deve mostrar a coordenada X, 
// o número de quadras “dentro” do nó, 
// o cep de algumas (poucas) quadras, 
// o x mínimo, 
// o x máximo 
// e o fator de balanceamento do nó.

// aquide conversão!
long get_rect_x_long(type_rect rect){
    double x = get_rect_x(rect);
    long longx = (long)x;
    return(longx);
}

void dmpt(type_dot DOTFILE, type_mMlavltree blocks_avl){
    QDC_DOTFILE = DOTFILE;
    void(*action_dot_ptr)(type_list, type_list, type_list, type_list, type_list, type_list);
    action_dot_ptr = action_dot_dmpt_;

    traverse_mMlavltree_full_tree_with_action_in_parent_list_and_childs_lists(blocks_avl, (void*)action_dot_ptr, (void*)get_rect_x_long);
}