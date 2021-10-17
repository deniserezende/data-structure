#include "qry_del_m_dm_mud.h"
#include <stdio.h>
#include <stdlib.h>

// AQUIDE fazer uma lista com tudo que vai no svg?


type_svg QDMDM_SVGFILE;
type_txt QDMDM_TXTFILE;
#define SIZE_DEFAULT_DOUBLE_STRING 10


void _QDMDM_report_property_txt_(type_property property){
    char *cardinal_direction = malloc(sizeof(char)*3);
    sprintf(cardinal_direction, "%c%c", get_property_cardinal_direction(property), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, get_property_cep(property));
    insert_string_in_txt(QDMDM_TXTFILE, cardinal_direction);
    char *number = malloc(sizeof(char) * 7);
    sprintf(number, "%d%c", get_property_house_number(property), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, number);
    insert_string_in_txt(QDMDM_TXTFILE, get_property_additional_address_data(property));

    free(cardinal_direction);
    free(number);
}

void _QDMDM_report_property_lease_txt_(type_property property){
    insert_string_in_txt(QDMDM_TXTFILE, get_property_lease_id(property));
    _QDMDM_report_property_txt_(property);
    
    char *area = malloc(sizeof(char) * SIZE_DEFAULT_DOUBLE_STRING);
    sprintf(area, "%lf%c", get_property_area(property), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, area);

    char *monthly_rent = malloc(sizeof(char) * SIZE_DEFAULT_DOUBLE_STRING);
    sprintf(monthly_rent, "%lf%c", get_property_monthly_rent(property), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, monthly_rent);

    free(area);
    free(monthly_rent);
}

void _QDMDM_report_person_txt_(type_person person){
    char *gender = malloc(sizeof(char)*3);
    char *name = get_person_full_name(person);
    sprintf(gender, "%c%c", get_person_gender(person), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, get_person_cpf(person));
    insert_string_in_txt(QDMDM_TXTFILE, name);
    insert_string_in_txt(QDMDM_TXTFILE, gender);
    insert_string_in_txt(QDMDM_TXTFILE, get_person_birthday(person));
    free(name);
    free(gender);
}

void _QDMDM_report_block_txt_(type_rect block_rect){
    type_block block_data = get_rect_data(block_rect);
    insert_string_in_txt(QDMDM_TXTFILE, get_block_cep(block_data));

    char *x_string = malloc(sizeof(char) * SIZE_DEFAULT_DOUBLE_STRING);
    sprintf(x_string, "%lf%c", get_rect_x(block_rect), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, x_string);

    char *y_string = malloc(sizeof(char) * SIZE_DEFAULT_DOUBLE_STRING);
    sprintf(y_string, "%lf%c", get_rect_y(block_rect), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, y_string);

    char *w_string = malloc(sizeof(char) * SIZE_DEFAULT_DOUBLE_STRING);
    sprintf(w_string, "%lf%c", get_rect_width(block_rect), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, w_string);

    char *h_string = malloc(sizeof(char) * SIZE_DEFAULT_DOUBLE_STRING);
    sprintf(h_string, "%lf%c", get_rect_height(block_rect), '\0');
    insert_string_in_txt(QDMDM_TXTFILE, h_string);
}


void _del_insert_svg(type_rect block_rect){
    type_block block_data = get_rect_data(block_rect);
    double x = get_rect_x(block_rect);
    double y = get_rect_y(block_rect);
    double w = get_rect_width(block_rect);
    double h = get_rect_height(block_rect);
    char color[8];
    sprintf(color, "black%c", '\0');

    insert_rectangle_in_svg(QDMDM_SVGFILE, x, y, w, h, get_rect_fill_color(block_rect), get_rect_stroke_color(block_rect), 2);
    // AQUIDE depois ver bonitinho que height colocar ao invés de h*2
    insert_line_in_svg(QDMDM_SVGFILE, (double)(x+w)/2, (double)(y+h)/2, (double)(x+w)/2, (double)h*2, color, 2);
    insert_text_in_svg(QDMDM_SVGFILE, (double)(x+w)/2, (double)h*2, color, get_block_cep(block_data), 20);
}

// Remove a quadra cep, os moradores que nela residirem e as ofertas de locação que nela existirem.
// No arquivo .svg: quadra deve ser colocada uma linha vertical com início no centro do elemento 
// removido até o topo do mapa. Também colocar (no topo) ao lado da linha vertical o cep.
// No arquivo .txt: reportar todos os dados relacionados aos elementos removidos.
type_mMlavltree del(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable people_table, type_hashtable property_leases, char block_cep[]){
    
    QDMDM_SVGFILE = SVGFILE;
    QDMDM_TXTFILE = TXTFILE;

    // Getting cep key to find element in hashtable
    long formatted_cep = format_cep_from_base36_to_base10(block_cep);
    set_id(block_cep); // from _auxiliary_function.h

    // AQUIDE verificar se apagando assim apaga também da avl, se seta pra null ou se da problema com os ponteiros
    // ajustei +-, verificar se agora ta apagando certo o block
    type_hashitem block_rect = delete_item_in_hash_table(blocks_table, formatted_cep, (void*)get_key_from_block, (void*)verify_block_found);
    if(block_rect == NULL){
        printf("Bloco Inexistente\n");
        return blocks_avl;
    }
    //type_mMlavltree block_avl = delete_item_in_mMl_avl_tree(blocks_avl, block_rect, (void*)compare_rectangles_by_x_coordinate);
    blocks_avl = delete_item_in_mMl_avl_tree(blocks_avl, block_rect, (void*)compare_rectangles_by_x_coordinate, (void*)compare_rect_blocks_cep);


    _del_insert_svg(block_rect);
    _QDMDM_report_block_txt_(block_rect);
    type_block block_data = get_rect_data(block_rect);
    remove_block(block_data);
    destroi_rectangle(block_rect);

    // DELETING PROPERTIES AND THEIR OWNERS
    type_hashitem property = delete_item_in_hash_table(properties_table, formatted_cep, (void*)get_property_cep_key, (void*)verify_property_found);
    while(property != NULL){
        _QDMDM_report_property_txt_(property);
        type_person owner = get_property_owner(property);
        if(owner != NULL){
            _QDMDM_report_person_txt_(owner);
            remove_owned_property_from_person(owner, 0);
            // set_id(get_person_cpf(owner));
            // type_hashitem del_owner = delete_item_in_hash_table(people_table, get_person_formatted_cpf(owner), (void*)get_person_formatted_cpf, (void*)verify_person_ptr);
            // remove_person(del_owner);
        }
        remove_property(property);

        // Next
        set_id(block_cep); // from _auxiliary_function.h
        property = delete_item_in_hash_table(properties_table, formatted_cep, (void*)get_property_cep_key, (void*)verify_property_found);
    }
    
    // PROPERTY LEASES
    long(*verify_property_leases_ptr)(type_property);
    verify_property_leases_ptr = verify_property_leases; // from _auxiliary_function.h

    type_hashitem property_lease = delete_item_in_hash_table(property_leases, formatted_cep, (void*)get_property_cep_key, (void*)verify_property_leases_ptr);
    while(property_lease != NULL){
        _QDMDM_report_property_lease_txt_(property_lease);
        int rent_status = get_property_rent_status(property_lease);
        // If it's not for rent then there is a tenant
        if(rent_status == 0){
            type_person tenant = get_property_tenant(property_lease);
            if(tenant != NULL){
                _QDMDM_report_person_txt_(tenant);
                remove_rented_property_from_person(tenant, 0);

                // set_id(get_person_cpf(tenant));
                // type_hashitem del_tenant = delete_item_in_hash_table(people_table, get_person_formatted_cpf(tenant), (void*)get_person_formatted_cpf, (void*)verify_person_ptr);
                // remove_person(del_tenant);
            }
        }
        remove_property(property);

        // Next
        set_id(block_cep); // from _auxiliary_function.h
        property_lease = delete_item_in_hash_table(property_leases, formatted_cep, (void*)get_property_cep_key, (void*)verify_property_leases_ptr);
    }

    // DUVIDA aqui remove também as pessoas que estiverem ocupando as locações ne?

    return blocks_avl;
}




long action_m_(type_property property){
    type_person owner = get_property_owner(property);
    _QDMDM_report_person_txt_(owner);
    _QDMDM_report_property_txt_(property);
    return 0;
}

// Moradores da quadra cujo cep é cep.
// TXT: listar todos os dados dos moradores(nome, endereço,...). 
// Reporta mensagem de erro se quadra não existir.
void m_(type_txt TXTFILE, type_hashtable blocks_table, type_hashtable properties_table, char block_cep[]){
    QDMDM_TXTFILE = TXTFILE;
    
    long formatted_cep = format_cep_from_base36_to_base10(block_cep);
    set_id(block_cep);
    
    long(*action_m_ptr)(type_property);
    action_m_ptr = action_m_;

    type_hashitem block = lookup_item_in_hash_table(blocks_table, formatted_cep, (void*)get_key_from_block, (void*)verify_block_found);
    if(block == NULL){
        printf("Erro, quadra não existe.\n");
        return;
    }

    traverse_hash_table_with_conditional_action_optimal(properties_table, formatted_cep, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_m_ptr);
}




void _dm_terminal(type_person person){
    char* name = get_person_full_name(person);
    printf("%s\n", get_person_cpf(person));
    printf("%s\n", name);
    printf("%c\n", get_person_gender(person));
    printf("%s\n", get_person_birthday(person));
    free(name);
}

void _dm_svg(type_person person, type_hashtable blocks_table){
    type_property property;

    if(does_person_own_properties(person)) property = get_person_owned_property(person, 0);
    else if(get_person_properties_leases(person)) property = get_person_property_lease(person, 0);
    else return;

    type_block block = lookup_item_in_hash_table(blocks_table, get_property_cep_key(property), (void*)get_key_from_block, (void*)verify_block_found);
    if(block == NULL) return;

    char color[8];
    sprintf(color, "blue%c", '\0');

    double x = get_rect_x(block);
    double y = get_rect_y(block);
    double h = get_rect_height(block);

    int house_number = get_property_house_number(property);

    insert_line_in_svg(QDMDM_SVGFILE, x+house_number, y+house_number, x+house_number, h*2, color, 2);
}

void _dm_txt(type_person person){
    _QDMDM_report_person_txt_(person);

    if(does_person_own_properties(person)){
        type_property owned_property = get_person_owned_property(person, 0);
        insert_string_in_txt(QDMDM_TXTFILE, "Moradia não é alugada");
        _QDMDM_report_property_txt_(owned_property);
    }
    if(get_person_properties_leases(person)){
        type_property rented_property = get_person_property_lease(person, 0);
        insert_string_in_txt(QDMDM_TXTFILE, "Moradia é alugada");
        _QDMDM_report_property_lease_txt_(rented_property);
    }

}
// Imprime todos os dados do morador identificado pelo cpf.
// TXT: dados pessoais, seu endereço e se moradia é alugada.
// SVG: colocar uma linha vertical do endereço do morador até a margem superior do mapa. 
// Anotar ao lado da linha o cpf, nome e endereço do morador
void dm_(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable people_table, char person_cpf[]){
    QDMDM_SVGFILE = SVGFILE;
    QDMDM_TXTFILE = TXTFILE;


    long cpf = format_cpf(person_cpf);
    set_id(person_cpf);

    // PERSON
    long(*verify_person_ptr)(type_person);
    verify_person_ptr = verify_person_found;

    type_hashitem person = lookup_item_in_hash_table(people_table, cpf, (void*)get_person_formatted_cpf, (void*)verify_person_ptr);

    if(person == NULL) return;

    _dm_txt(person);
    _dm_terminal(person);
    _dm_svg(person, blocks_table);
}






void _mud_txt(type_person person, type_property old_property, type_property new_property){
    _QDMDM_report_person_txt_(person);

    insert_string_in_txt(QDMDM_TXTFILE, "Endereço antigo:");
    _QDMDM_report_property_txt_(old_property);

    insert_string_in_txt(QDMDM_TXTFILE, "Endereço novo:");
    _QDMDM_report_property_txt_(new_property);
}


// AQUIDE é para a propriedade antiga aparecer no svg?
// se sim ver como vou fazer para ela aparecer... 
// se eu colocar aqui dps o bloco tampa ?????
void _mud_svg(type_property old_property, type_property new_property, type_rect old_block, type_rect new_block){
    double old_x = get_rect_x(old_block);
    double old_y = get_rect_y(old_block);
    double new_x = get_rect_x(new_block);
    double new_y = get_rect_y(new_block);

    char color_red[8], color_white[8], color_blue[8], color_black[8];
    sprintf(color_red, "red%c", '\0');
    sprintf(color_white, "white%c", '\0');
    sprintf(color_blue, "blue%c", '\0');
    sprintf(color_black, "black%c", '\0');

    int old_house_number = get_property_house_number(old_property);
    int new_house_number = get_property_house_number(new_property);
    char *old_cep = get_property_cep(old_property);
    char *new_cep = get_property_cep(new_property);

    insert_line_in_svg(QDMDM_SVGFILE, old_x+old_house_number, old_y+old_house_number, new_x+new_house_number, new_y+new_house_number, color_red, 4);
    insert_circle_in_svg(QDMDM_SVGFILE, old_x+old_house_number, old_y+old_house_number, 4, color_red, color_white, 2);
    insert_circle_in_svg(QDMDM_SVGFILE, new_x+new_house_number, new_y+new_house_number, 4, color_blue, color_white, 2);
    insert_text_in_svg(QDMDM_SVGFILE, old_x+old_house_number, old_y+old_house_number, color_black, old_cep, 8);
    insert_text_in_svg(QDMDM_SVGFILE, new_x+new_house_number, new_y+new_house_number, color_black, new_cep, 8);
}

// A pessoa identificada por cpf muda-se para o endereço determinado pelos parâmetros.
// TXT: Mostrar os dados da pessoa (nome, etc), o endereço antigo e o novo endereço.
// SVG: Uma linha vermelha grossa do endereço antigo ao endereço novo. 
// Um pequeno círculo vermelho no endereço antigo, outro círculo azul no novo endereço. 
// Ambos círculos com borda branca grossa.
void mud(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable people_table, type_hashtable properties_table, char person_cpf[], char property_cep[], char cardinal_direction, int house_number, char addicional_data[]){
    QDMDM_SVGFILE = SVGFILE;
    QDMDM_TXTFILE = TXTFILE;
    long cpf = format_cpf(person_cpf);
    set_id(person_cpf);

    // PERSON
    long(*verify_person_ptr)(type_person);
    verify_person_ptr = verify_person_found;

    type_hashitem person = lookup_item_in_hash_table(people_table, cpf, (void*)get_person_formatted_cpf, (void*)verify_person_ptr);

    if(person == NULL) return;

    long new_cep_key = format_cep_from_base36_to_base10(property_cep);
    type_property new_property_ = new_property(property_cep, cardinal_direction, house_number, addicional_data);
    type_property old_property = remove_owned_property_from_person(person, 0);    
    char* old_cep = get_property_cep(old_property);
    char* new_cep = get_property_cep(new_property_);
    long old_cep_key = get_property_cep_key(old_property);

    set_owned_properties_to_person(person, 1);
    add_persons_owned_property(person, new_property_);
    add_property_owner(new_property_, person);
    insert_item_in_hash_table(properties_table, new_property_, new_cep_key, (void*)get_property_cep_key, (void*)compare_properties_cep);

    long(*get_key_from_block_ptr)(type_block);
    get_key_from_block_ptr = get_key_from_block;

    long(*verify_block_found_ptr)(type_block);
    verify_block_found_ptr = verify_block_found;

    set_id(old_cep);
    type_rect old_block = lookup_item_in_hash_table(blocks_table, old_cep_key, (void*)get_key_from_block_ptr, (void*)verify_block_found_ptr);
    set_id(new_cep);
    type_rect new_block = lookup_item_in_hash_table(blocks_table, new_cep_key, (void*)get_key_from_block_ptr, (void*)verify_block_found_ptr);

    _mud_txt(person, old_property, new_property_);
    if(old_block == NULL || new_block == NULL ) return;
    _mud_svg(old_property, new_property_, old_block, new_block);
}
