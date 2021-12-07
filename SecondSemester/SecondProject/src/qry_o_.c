#include <stdio.h>
#include "qry_o_.h"


int _find_minimum_distance_to_property_o_(type_hashtable cityblocks_hash, type_property property, double minimum_distance_point[2]){
    char* cep = get_property_cep(property);
    long cep_key = format_cep_from_base36_to_base10(cep);

    set_id(cep);
    type_hashitem block = lookup_item_in_hash_table(cityblocks_hash, cep_key, (void*)get_key_from_block, (void*)verify_block_found);
    if(block == NULL){
        printf("Bloco correspondente ao cep dado não foi encontrado\n");
        return 0;
    }
    double x = get_rect_x(block);
    double y = get_rect_y(block);
    double w = get_rect_width(block);
    double h = get_rect_height(block);


    int house_number = get_property_house_number(property);
    char cardinal_direction = get_property_cardinal_direction(property);

    int shift_amount_x = 0;
    int shift_amount_y = 0;
    switch (cardinal_direction) {
    case 'N':
        shift_amount_x = house_number;
        shift_amount_y = h;
        break;
    case 'S':
        shift_amount_x = house_number;
        shift_amount_y = 0;
        break;
    case 'O':
        shift_amount_x = 0;
        shift_amount_y = house_number;
        break;
    case 'L':
        shift_amount_x = w;
        shift_amount_y = house_number;
        break;
    default:
        break;
    }

    double dist = __INT_MAX__;

    double dist_one = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x, y);
    if(dist_one < dist){
        dist = dist_one;
        minimum_distance_point[0] = x;
        minimum_distance_point[1] = y;
    }
    double dist_two = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x, y+h);
    if(dist_two < dist){
        dist = dist_two;
        minimum_distance_point[0] = x;
        minimum_distance_point[1] = y+h;
    }
    double dist_three = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x+w, y);
    if(dist_three < dist){
        dist = dist_three;
        minimum_distance_point[0] = x+w;
        minimum_distance_point[1] = y;
    }
    double dist_four = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x+w, y+h);
    if(dist_four < dist){
        dist = dist_four;
        minimum_distance_point[0] = x+w;
        minimum_distance_point[1] = y+h;  
    }
    return 1;
}

// Armazena no registrador r a posição geográfica
// do endereço cep/face/num
// SVG: linha vertical com identificação do
// registrador.
type_property o_(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_hash, char cep[], char cardinal_direction, int house_number, double viewbox[]){
    type_property property = new_property(cep, cardinal_direction, house_number, "-");
    // txt output
    set_txt_file(TXTFILE);
    _report_property_txt_(property);

    // svg output
    double x_y[2];
    int found_minimum_distance = _find_minimum_distance_to_property_o_(blocks_hash, property, x_y);
    if(found_minimum_distance == 0) return NULL;
    insert_line_in_svg(SVGFILE, x_y[0], x_y[1], x_y[0], viewbox[1], "Purple", 2);
    char house_number_string[10];
    sprintf(house_number_string, "%d", house_number);
    char text[100];
    sprintf(text, "@o? cep=%s  face=%c  número=%s", cep, cardinal_direction, house_number_string);
    insert_text_in_svg(SVGFILE, x_y[0], viewbox[1] - 5, "Purple", text, 10);
    return property;
}