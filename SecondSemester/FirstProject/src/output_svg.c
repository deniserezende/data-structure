//
//  output_svg.c
//  
//
//  Created by Denise F. de Rezende on 18/09/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "output_svg.h"


// GLOBAL VARIABLES
type_svg CRV_svgfile;
type_hashtable CRV_blocks;
type_hashtable CRV_people;
type_hashtable CRV_properties;
char cep_global[40];

long returns_true_function(type_mMlavlitems item){
    return 1;
}

void insert_blocks_in_svg_aux(type_rect rect){
    double x, y, w, h;
    char *stroke, *fill;
    type_block block = get_rect_data(rect);
    char color[8];
    sprintf(color, "black%c", '\0');
    char* cep = get_block_cep(block);
    x = get_rect_x(rect);
    y = get_rect_y(rect);
    w = get_rect_width(rect);
    h = get_rect_height(rect);
    stroke = get_rect_stroke_color(rect);
    fill = get_rect_fill_color(rect);
    insert_rectangle_in_svg(CRV_svgfile, x, y, w, h, fill, stroke, 1);
    insert_text_in_svg(CRV_svgfile, x+w/2, y+h/2, color, cep, 10);
}

long traverse_side_insert_blocks_in_svg_aux(type_rect rect, type_rect rect1, type_rect rect2, type_rect rect3, type_rect rect4){
    return 11;
}

// Insert blocks in svg
void insert_blocks_in_svg(type_svg svgfile, type_mMlavltree blocks){
    CRV_svgfile = svgfile;

    void(*ptr_insert)(type_mMlavlitems);
    ptr_insert= insert_blocks_in_svg_aux;

    long(*ptr_true)(type_mMlavlitems);
    ptr_true = returns_true_function;

    long(*ptr_traverse)(type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems, type_mMlavlitems);
    ptr_traverse = traverse_side_insert_blocks_in_svg_aux;

    traverse_mMlavltree_with_conditional_action(blocks, (void*)ptr_traverse, (void*)ptr_true, (void*)ptr_insert);
    //traverse_full_hash_table_with_conditional_action(blocks, (void*)ptr_true, (void*)ptr_insert);
}

long check_cep_aux(type_rect block){ 
    char* cep_found = get_block_cep(block);
    if(strcmp(cep_found, cep_global) == 0) return 1;
    return 0; 
}

long get_key_from_block_aux(type_rect block){
    type_block block_data = get_rect_data(block);
    return(get_block_formatted_cep(block_data));
}

void insert_people_in_svg_aux(type_person person){
    long condition = does_person_own_properties(person);
    if(!condition){
        return;
    }

    type_property property = get_person_owned_property(person, 0);
    int property_numb = get_property_number(property);
    long key = get_property_cep_key(property);
    sprintf(cep_global, "%s%c", get_property_cep(property), '\0');

    long(*ptr_check_cep)(type_hashitem);
    ptr_check_cep = check_cep_aux;

    long(*ptr_get_key)(type_hashtable);
    ptr_get_key = get_key_from_block_aux;

    type_rect block = lookup_item_in_hash_table(CRV_blocks, key, (void*)ptr_get_key, (void*)ptr_check_cep);
    if(block == NULL){
        return;
    }

    double x = get_rect_x(block) + property_numb;
    double y = get_rect_y(block) + property_numb;
    double r = (get_rect_width(block) + get_rect_height(block)) / 10;

    insert_circle_in_svg(CRV_svgfile, x, y, r, "pink", "pink", 1);
}

// Insert people in svg
void insert_people_in_svg(type_svg svgfile, type_hashtable people, type_hashtable blocks){
    CRV_svgfile = svgfile;
    CRV_people = people;
    CRV_blocks = blocks;

    void(*ptr_insert)(type_hashitem);
    ptr_insert = insert_people_in_svg_aux;
    
    long(*ptr_true)(type_hashitem);
    ptr_true = returns_true_function;

    traverse_full_hash_table_with_conditional_action(blocks, (void*)ptr_true, (void*)ptr_insert);
}

void insert_properties_in_svg_aux(type_property property){
    int property_numb = get_property_number(property);
    long key = get_property_cep_key(property);
    sprintf(cep_global, "%s%c", get_property_cep(property), '\0');

    long(*ptr_check_cep)(type_hashitem);
    ptr_check_cep = check_cep_aux;

    long(*ptr_get_key)(type_hashtable);
    ptr_get_key = get_key_from_block_aux;

    type_rect block = lookup_item_in_hash_table(CRV_blocks, key, (void*)ptr_get_key, (void*)ptr_check_cep);
    if(block == NULL){
        return;
    }

    double x = get_rect_x(block) + property_numb;
    double y = get_rect_y(block) + property_numb;
    double height = get_rect_height(block);
    double width = get_rect_width(block);
    insert_rectangle_in_svg(CRV_svgfile, x, y, width/3, height/3, "blue", "blue", 1);
}

// Insert property in svg
void insert_properties_in_svg(type_svg svgfile, type_hashtable properties, type_hashtable blocks){
    CRV_svgfile = svgfile;
    CRV_properties = properties;
    CRV_blocks = blocks;

    void(*ptr_insert)(type_hashitem);
    ptr_insert = insert_properties_in_svg_aux;

    long(*ptr_true)(type_hashitem);
    ptr_true = returns_true_function;

    traverse_full_hash_table_with_conditional_action(blocks, (void*)ptr_true, (void*)ptr_insert);
}

int insert_svg_file_in_other_svg_file(char* origin_svgfilename, type_svg destination_svgfile){
    FILE *origin = fopen(origin_svgfilename, "r");
    if(origin == NULL) return 0;
    FILE *destination = destination_svgfile;
    if(destination == NULL) return 0;
    char *line = (char*)malloc(500 * sizeof(char));
    while(!feof(origin)){ 
        fscanf(origin, "\n%[^\n]\ns", line);
        if(strncmp(line,"<svg ", 4) != 0 && strcmp(line,"xmlns=\"http://www.w3.org/2000/svg\"") != 0 && strcmp(line,"xmlns:xlink=\"http://www.w3.org/1999/xlink\" >") != 0){
            if(strcmp(line, "</svg>") != 0){
                insert_string_in_svg(destination, line);
            }
        }
    }
    free(line);
    return 1;
}
