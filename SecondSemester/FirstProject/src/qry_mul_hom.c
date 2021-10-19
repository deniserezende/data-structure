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

void action_property_mul_(type_hashitem property){
    char color[7];
    sprintf(color, "pink%c", '\0');
    type_person owner = get_property_owner(property);
    if(owner != NULL){
    char gender = get_person_gender(owner);
        if(gender == 'F'){
            _report_person_txt_(owner);
            _report_property_txt_(property);

            //SVG
            int house_number = get_property_house_number(property);
            char cardinal_direction = get_property_cardinal_direction(property);

                int shift_amount_x = 0;
                int shift_amount_y = 0;
                switch (cardinal_direction) {
                case 'N':
                    shift_amount_x = house_number;
                    shift_amount_y = QMH_h;
                    break;
                case 'S':
                    shift_amount_x = house_number;
                    shift_amount_y = 0;
                    break;
                case 'L':
                    shift_amount_x = 0;
                    shift_amount_y = house_number;
                    break;
                case 'O':
                    shift_amount_x = QMH_w;
                    shift_amount_y = house_number;
                    break;
                default:
                    break;
                }
            insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+house_number, QMH_y1+house_number, 6, 2, color, color, 1);
        }
    }
}

void action_property_lease_mul_(type_hashitem property){
    char color[7];
    sprintf(color, "pink%c", '\0');
    if(!get_property_rent_status(property)){

        type_person tenant = get_property_tenant(property);
        if(tenant != NULL){
            char gender = get_person_gender(tenant);
            if(gender == 'F'){
                _report_person_txt_(tenant);
                _report_property_lease_txt_(property);

                //SVG
                int house_number = get_property_house_number(property);
                char cardinal_direction = get_property_cardinal_direction(property);

                int shift_amount_x = 0;
                int shift_amount_y = 0;
                switch (cardinal_direction) {
                case 'N':
                    shift_amount_x = house_number;
                    shift_amount_y = QMH_h;
                    break;
                case 'S':
                    shift_amount_x = house_number;
                    shift_amount_y = 0;
                    break;
                case 'L':
                    shift_amount_x = 0;
                    shift_amount_y = house_number;
                    break;
                case 'O':
                    shift_amount_x = QMH_w;
                    shift_amount_y = house_number;
                    break;
                default:
                    break;
                }
                insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+house_number, QMH_y1+house_number, 6, 2, color, color, 1);

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

    set_id(get_block_cep(block));
    traverse_hash_table_with_conditional_action_optimal(QMH_properties_table, cep, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_property_ptr);
    set_id(get_block_cep(block));
    traverse_full_hash_table_with_conditional_action(QMH_property_leases, (void*)verify_property_leases, (void*)action_property_lease_ptr);
    return 0;
}

// Semelhante a hom. Seleciona as mulheres. Pinta a elipse de rosa.
void mul(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable properties_table, type_hashtable property_leases, double x, double y, double w, double h){
    QMH_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);

    QMH_property_leases = property_leases;
    QMH_properties_table = properties_table;

    long(*action_ptr)(type_mMlavlitems);
    action_ptr = action_mul;

    set_x1_x2_y1_y2(x, x+w, y, y+h);
    traverse_mMlavltree_with_conditional_action(blocks_avl, (void*)traverse_side_rect_in_rect_, (void*)condition_rect_in_rect_, (void*)action_ptr);   
}


// ------------------------------------------------------------------------------------------------------------------------------------------------


void action_property_hom_(type_hashitem property){
    char color[7];
    sprintf(color, "blue%c", '\0');
    sprintf(color, "blue%c", '\0');
    type_person owner = get_property_owner(property);
    if(owner != NULL){
        char gender = get_person_gender(owner);
        if(gender == 'M'){
            _report_person_txt_(owner);
            _report_property_txt_(property);
            //SVG
            int house_number = get_property_house_number(property);
            char cardinal_direction = get_property_cardinal_direction(property);

            int shift_amount_x = 0;
            int shift_amount_y = 0;
            switch (cardinal_direction) {
            case 'N':
                shift_amount_x = house_number;
                shift_amount_y = QMH_h;
                break;
            case 'S':
                shift_amount_x = house_number;
                shift_amount_y = 0;
                break;
            case 'L':
                shift_amount_x = 0;
                shift_amount_y = house_number;
                break;
            case 'O':
                shift_amount_x = QMH_w;
                shift_amount_y = house_number;
                break;
            default:
                break;
            }
            insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+shift_amount_x, QMH_y1+shift_amount_y, 6, 2, color, color, 1);
        }
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
                _report_person_txt_(tenant);
                _report_property_lease_txt_(property);

                //SVG
                int house_number = get_property_house_number(property);
                char cardinal_direction = get_property_cardinal_direction(property);

                int shift_amount_x = 0;
                int shift_amount_y = 0;
                switch (cardinal_direction) {
                case 'N':
                    shift_amount_x = house_number;
                    shift_amount_y = QMH_h;
                    break;
                case 'S':
                    shift_amount_x = house_number;
                    shift_amount_y = 0;
                    break;
                case 'L':
                    shift_amount_x = 0;
                    shift_amount_y = house_number;
                    break;
                case 'O':
                    shift_amount_x = QMH_w;
                    shift_amount_y = house_number;
                    break;
                default:
                    break;
                }
                insert_ellipse_in_svg(QMH_SVGFILE, QMH_x1+shift_amount_x, QMH_y1+shift_amount_y, 6, 2, color, color, 1);
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

    set_id(get_block_cep(block));
    traverse_hash_table_with_conditional_action_optimal(QMH_properties_table, cep, (void*)get_property_cep_key, (void*)verify_property_found, (void*)action_property_ptr);
    set_id(get_block_cep(block));
    traverse_full_hash_table_with_conditional_action(QMH_property_leases, (void*)verify_property_leases, (void*)action_property_lease_ptr);
    return;
}

// Homens que moram dentro da região especificada.
// TXT: reportar dados da pessoa e da moradia 
// SVG: marcar posição da moradia com uma pequena elipse azul.
void hom(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable properties_table, type_hashtable property_leases, double x, double y, double w, double h){
    QMH_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);

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
