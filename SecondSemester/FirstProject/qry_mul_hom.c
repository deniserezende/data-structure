#include "qry_mul_hom.h"
#include <stdio.h>
#include <stdlib.h>

double QMH_x1, QMH_x2;
double QMH_y1, QMH_y2;
double QMH_w, QMH_h;
type_hashtable QMH_property_leases, QMH_properties_table;
char QMH_cep[40];
type_svg QMH_SVGFILE;
type_txt QMH_TXTFILE;

#define QMH_SIZE_DOUBLESTR 10

void _QMH_report_property_txt_(type_property property){
    char *cardinal_direction = malloc(sizeof(char)*3);
    sprintf(cardinal_direction, "%c%c", get_property_cardinal_direction(property), '\0');
    insert_string_in_txt(QMH_TXTFILE, get_property_cep(property));
    insert_string_in_txt(QMH_TXTFILE, cardinal_direction);
    char *number = malloc(sizeof(char) * 7);
    sprintf(number, "%d%c", get_property_house_number(property), '\0');
    insert_string_in_txt(QMH_TXTFILE, number);
    insert_string_in_txt(QMH_TXTFILE, get_property_additional_address_data(property));

    free(cardinal_direction);
    free(number);
}

void _QMH_report_property_lease_txt_(type_property property){
    insert_string_in_txt(QMH_TXTFILE, get_property_lease_id(property));
    _QMH_report_property_txt_(property);
    
    char *area = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(area, "%.2lf%c", get_property_area(property), '\0');
    insert_string_in_txt(QMH_TXTFILE, area);

    char *monthly_rent = malloc(sizeof(char) * QDC_SIZE_DOUBLESTR);
    sprintf(monthly_rent, "%.2lf%c", get_property_monthly_rent(property), '\0');
    insert_string_in_txt(QMH_TXTFILE, monthly_rent);

    free(area);
    free(monthly_rent);
}

void _QMH_report_person_txt_(type_person person){
    char *gender = malloc(sizeof(char)*3);
    char *name = get_person_full_name(person);
    sprintf(gender, "%c%c", get_person_gender(person), '\0');
    insert_string_in_txt(QMH_TXTFILE, get_person_cpf(person));
    insert_string_in_txt(QMH_TXTFILE, name);
    insert_string_in_txt(QMH_TXTFILE, gender);
    insert_string_in_txt(QMH_TXTFILE, get_person_birthday(person));
    free(name);
    free(gender);
}



void action_property_mul_(type_hashitem property){
    char color[7];
    sprintf(color, "blue%c", '\0');
    type_person owner = get_property_owner(property);
    char gender = get_person_gender(owner);
    if(gender == 'F'){
        _QMH_report_person_txt_(owner);
        _QMH_report_property_txt_(property);

        //SVG
        int house_number = get_property_house_number(property);
        insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+house_number, QMH_y1+house_number, 3, 1, color, color, 1);
    }
}

void action_property_lease_mul_(type_hashitem property){
    char color[7];
    sprintf(color, "blue%c", '\0');
    if(!get_property_rent_status(property)){

        type_person tenant = get_property_tenant(property);
        if(tenant != NULL){
            char gender = get_person_gender(tenant);
            if(gender == 'F'){
                _QMH_report_person_txt_(tenant);
                _QMH_report_property_lease_txt_(property);

                //SVG
                int house_number = get_property_house_number(property);
                insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+house_number, QMH_y1+house_number, 3, 1, color, color, 1);

            }   
        }
    }
}

long action_mul(type_mMlavlitems block_rect){
    type_block block = get_rect_data(block_rect);
    long cep = get_block_formatted_cep(block);
    sprintf(QMH_cep, "%s%c", get_block_cep(block), '\0');

    void(*action_property_ptr)(type_property);
    action_property_ptr = action_property_mul_;

    void(*action_property_lease_ptr)(type_property);
    action_property_lease_ptr = action_property_lease_mul_;

    QMH_x1 = get_rect_x(block_rect);
    QMH_y1 = get_rect_y(block_rect);
    QMH_h = get_rect_height(block_rect); 
    QMH_w = get_rect_width(block_rect);

    traverse_hash_table_with_conditional_action_optimal(QMH_properties_table, cep, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_property_ptr);
    traverse_hash_table_with_conditional_action_optimal(QMH_property_leases, cep, (void*)get_property_cep_key, (void*)verify_property_leases, (void*)action_property_lease_ptr);

    return 0;
}

// Semelhante a hom. Seleciona as mulheres. Pìnta a elipse de rosa.
void mul(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable properties_table, type_hashtable property_leases, type_hashtable people_table, double x, double y, double w, double h){
    QMH_SVGFILE = SVGFILE;
    QMH_TXTFILE = TXTFILE;

    QMH_property_leases = property_leases;
    QMH_properties_table = properties_table;

    long(*action_ptr)(type_mMlavlitems);
    action_ptr = action_mul;

    set_x1_x2_y1_y2(x, x+w, y, y+h);
    traverse_mMlavltree_with_conditional_action(blocks_avl, (void*)traverse_side_rect_in_rect_, (void*)condition_rect_in_rect_, (void*)action_ptr);   
}




void action_property_hom_(type_hashitem property){
    char color[7];
    sprintf(color, "blue%c", '\0');
    type_person owner = get_property_owner(property);
    char gender = get_person_gender(owner);
    if(gender == 'M'){
        _QMH_report_person_txt_(owner);
        _QMH_report_property_txt_(property);

        //SVG
        int house_number = get_property_house_number(property);
        insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+house_number, QMH_y1+house_number, 3, 1, color, color, 1);
    }
}

void action_property_lease_hom_(type_hashitem property){
    char color[7];
    sprintf(color, "blue%c", '\0');

    if(!get_property_rent_status(property)){

        type_person tenant = get_property_tenant(property);
        if(tenant != NULL){
            char gender = get_person_gender(tenant);
            if(gender == 'M'){
                _QMH_report_person_txt_(tenant);
                _QMH_report_property_lease_txt_(property);

                //SVG
                int house_number = get_property_house_number(property);
                insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+house_number, QMH_y1+house_number, 3, 1, color, color, 1);

            }   
        }
    }
}

void action_hom(type_mMlavlitems block_rect){
    type_block block = get_rect_data(block_rect);
    long cep = get_block_formatted_cep(block);
    sprintf(QMH_cep, "%s%c", get_block_cep(block), '\0');


    void(*action_property_ptr)(type_property);
    action_property_ptr = action_property_hom_;

    void(*action_property_lease_ptr)(type_property);
    action_property_lease_ptr = action_property_lease_hom_;

    QMH_x1 = get_rect_x(block_rect);
    QMH_y1 = get_rect_y(block_rect);
    QMH_h = get_rect_height(block_rect); 
    QMH_w = get_rect_width(block_rect);


    traverse_hash_table_with_conditional_action_optimal(QMH_properties_table, cep, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_property_ptr);
    traverse_hash_table_with_conditional_action_optimal(QMH_property_leases, cep, (void*)get_property_cep_key, (void*)verify_property_leases, (void*)action_property_lease_ptr);

    return;
}

// Homens que moram dentro da região especificada.
// TXT: reportar dados da pessoa e da moradia SVG: marcar posição da moradia com uma pequena elipse azul.
void hom(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable properties_table, type_hashtable property_leases, type_hashtable people_table, double x, double y, double w, double h){
    QMH_SVGFILE = SVGFILE;
    QMH_TXTFILE = TXTFILE;

    QMH_property_leases = property_leases;
    QMH_properties_table = properties_table;

    void(*action_ptr)(type_mMlavlitems);
    action_ptr = action_hom;
    //action_hom;

    long(*traverse_ptr)(type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems);
    traverse_ptr = traverse_side_rect_in_rect_;

    long(*condition_ptr)(type_mMlavlitems);
    condition_ptr = condition_rect_in_rect_;

    set_x1_x2_y1_y2(x, x+w, y, y+h);
    traverse_mMlavltree_with_conditional_action(blocks_avl, (void*)traverse_ptr, (void*)condition_ptr, (void*)action_ptr);    
}
