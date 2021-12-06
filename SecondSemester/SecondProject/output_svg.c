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

long returns_true_function(void* item){
    return 1;
}

long returns_true_function_wthree(void* item, void* item2, void* item3){
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


void insert_vertex_in_svg_aux(type_vertex vertex){
    double x, y, w, h;
    x = get_vertex_x(vertex);
    y = get_vertex_y(vertex);
    char color[8];
    sprintf(color, "black%c", '\0');
    insert_circle_in_svg(CRV_svgfile, x, y, 1, color, color, 1);
}


void insert_edge_in_svg_aux(type_vertex from_vertex, type_edge edge, type_vertex to_vertex){
    double x1, y1, x2, y2;
    x1 = get_vertex_x(from_vertex);
    y1 = get_vertex_y(from_vertex);
    x2 = get_vertex_x(to_vertex);
    y2 = get_vertex_y(to_vertex);
    char color[8];
    sprintf(color, "black%c", '\0');
    double length = get_edge_length(edge);

    insert_line_in_svg(CRV_svgfile, x1, y1, x2, y2, color, 1);
}


// Insert via in svg
void insert_via_in_svg(type_svg svgfile, type_graph via_graph){
    CRV_svgfile = svgfile;

    void(*vertex_action)(type_vertex);
    vertex_action= insert_vertex_in_svg_aux;

    void(*edge_action)(type_vertex, type_edge, type_vertex);
    edge_action= insert_edge_in_svg_aux;

    long(*ptr_true)(type_graphinfos);
    ptr_true = returns_true_function;

    traverse_graph_conditional_actions(via_graph, (void*)vertex_action, (void*)ptr_true, (void*)edge_action, (void*)returns_true_function_wthree);
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

int insert_svg_file_in_other_svg_file(char* origin_svgfilename, type_svg destination_svgfile){
    FILE *origin = fopen(origin_svgfilename, "r");
    if(origin == NULL) return 0;
    FILE *destination = destination_svgfile;
    if(destination == NULL) return 0;
    char *line = (char*)malloc(20000 * sizeof(char));
    while(!feof(origin)){ 
        fscanf(origin, "\n%[^\n]\ns", line);
        //printf("[%ld]\n", strlen(line));
        //printf("[%s]\n", line);
        if(strncmp(line,"<svg ", 4) != 0 && strcmp(line,"xmlns=\"http://www.w3.org/2000/svg\"") != 0 && strcmp(line,"xmlns:xlink=\"http://www.w3.org/1999/xlink\" >") != 0){
            if(strcmp(line, "</svg>") != 0){
                insert_string_in_svg(destination, line);
            }
        }
    }
    free(line);
    return 1;
}
