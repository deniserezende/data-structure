//
//  output_svg.c
//  
//
//  Created by Denise F. de Rezende on 09/06/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "output_svg.h"

// GLOBAL VARIABLES
type_svg CRV_svgfile;
type_kdtree CRV_circles, CRV_rects;


long condition_true_aux(type_rect rect){
    return 1;
}

long check_if_rect_is_active_aux(type_rect rect){
    type_building building = get_rect_data(rect);
    return((long)is_building_active(building));
}

void insert_rect_in_svg_aux(type_rect rect){
    double x, y, w, h;
    char *stroke, *fill;
    x = get_rect_x(rect);
    y = get_rect_y(rect);
    w = get_rect_width(rect);
    h = get_rect_height(rect);
    stroke = get_rect_stroke_color(rect);
    fill = get_rect_fill_color(rect);
    insert_rectangle_in_svg(CRV_svgfile, x, y, w, h, fill, stroke, 1);
}

void insert_active_rects_in_svg(type_svg svgfile, type_kdtree rects){
    if(empty_kdtree(rects)) return;
    CRV_svgfile = svgfile;
    CRV_rects = rects;
    long(*ptr_only_active_rects)(type_kdtitems);
    ptr_only_active_rects = check_if_rect_is_active_aux;
    void(*ptr_insert_rect)(type_kdtitems);
    ptr_insert_rect = insert_rect_in_svg_aux;

    traverse_full_kdtree_with_conditional_action(rects, (void*)ptr_only_active_rects, (void*)ptr_insert_rect);
}

void insert_rects_in_svg(type_svg svgfile, type_kdtree rects){
    if(empty_kdtree(rects)) return;
    CRV_svgfile = svgfile;
    CRV_rects = rects;
    long(*ptr_true)(type_kdtitems);
    ptr_true = condition_true_aux;
    void(*ptr_insert_rect)(type_kdtitems);
    ptr_insert_rect = insert_rect_in_svg_aux;

    traverse_full_kdtree_with_conditional_action(rects, (void*)ptr_true, (void*)ptr_insert_rect);
} 

void insert_one_rect_in_svg(type_svg svgfile, type_rect rect){
    double x, y, w, h;
    char *stroke, *fill;
    x = get_rect_x(rect);
    y = get_rect_y(rect);
    w = get_rect_width(rect);
    h = get_rect_height(rect);
    stroke = get_rect_stroke_color(rect);
    fill = get_rect_fill_color(rect);
    insert_rectangle_in_svg(svgfile, x, y, w, h, fill, stroke, 1);
}


void insert_circle_in_svg_aux(type_circle circle){
    double x, y, r;
    char *stroke, *fill;
    x = get_circle_x(circle);
    y = get_circle_y(circle);
    r = get_circle_radius(circle);
    stroke = get_circle_stroke_color(circle);
    fill = get_circle_fill_color(circle);
    insert_circle_in_svg(CRV_svgfile, x, y, r, fill, stroke, 1);
}

void insert_circles_in_svg(type_svg svgfile, type_kdtree circles){
    if(empty_kdtree(circles)) return; 
    CRV_svgfile = svgfile;
    CRV_circles = circles;
    long(*ptr_true)(type_kdtitems);
    ptr_true = condition_true_aux;
    void(*ptr_insert_circle)(type_kdtitems);
    ptr_insert_circle = insert_circle_in_svg_aux;

    traverse_full_kdtree_with_conditional_action(circles, (void*)ptr_true, (void*)ptr_insert_circle);
}

void insert_person_considering_status_aux(type_circle circle){
    type_person person = get_circle_data(circle);
    double x, y, r;
    double *x2 = malloc(sizeof(double));
    double *y2 = malloc(sizeof(double));
    char *stroke, *fill;
    x = get_circle_x(circle);
    y = get_circle_y(circle);
    r = get_circle_radius(circle);
    if(!is_person_alive(person)){
        insert_circle_in_svg_aux(circle);

        insert_line_in_svg(CRV_svgfile, x-r-0.2, y, x+r-0.2, y, "White", 1);
        insert_line_in_svg(CRV_svgfile, x, y-r-0.2, x, y+r-0.2, "White", 1);
    }
    else{
        if(!is_person_active(person)){
            get_where_person_went(person, x2, y2);
            stroke = get_circle_stroke_color(circle);
            fill = get_circle_fill_color(circle);
            insert_animated_circle_in_svg(CRV_svgfile, x, y, *x2, *y2, r, fill, stroke, 1, "transparent", 1, "Black", 0.5, 10, "indefinite");
        }
        else insert_circle_in_svg_aux(circle);
    }
    free(x2);
    free(y2);
}

void insert_circles_considering_status_in_svg(type_svg svgfile, type_kdtree circles){
    if(empty_kdtree(circles)) return; 
    CRV_svgfile = svgfile;
    long(*ptr_true)(type_kdtitems);
    ptr_true = condition_true_aux;
    void(*ptr_insert_circle)(type_kdtitems);
    ptr_insert_circle = insert_person_considering_status_aux;

    traverse_full_kdtree_with_conditional_action(circles, (void*)ptr_true, (void*)ptr_insert_circle);
}



long insert_meteor_in_svg_aux(type_meteor meteor){
    double x = get_meteor_x(meteor);
    double y = get_meteor_y(meteor);
    double rad = get_meteor_radiation_level(meteor);
    char color[6];
    sprintf(color, "Grey%c", '\0');
    insert_circle_with_different_opacity_in_svg(CRV_svgfile, x, y, rad/5, color, color, 0.8, 2);

    return 0;
}

void insert_meteors_in_svg(type_svg svgfile, type_list meteors){ 
    if(empty_list(meteors)) return;  
    CRV_svgfile = svgfile;
    long(*ptr_true)(type_litems);
    ptr_true = condition_true_aux;
    long(*ptr_insert_meteor)(type_litems);
    ptr_insert_meteor = insert_meteor_in_svg_aux;
    traverse_full_list_with_conditional_action(meteors, (void*)ptr_true, (void*)ptr_insert_meteor);
}



void fg_report_svg_action_aux(type_rect rect){
    type_building building;
    
    // Checks if building is active. 
    building = get_rect_data(rect);
    if(!is_building_active(building)) return;

    int amount = get_amount_of_people_inside_building(building);

    double rectx = get_rect_x(rect);
    double recty = get_rect_y(rect);
    char *svgtext = malloc(sizeof(char) * 10);
    sprintf(svgtext,"%d", amount);
    insert_text_in_svg(CRV_svgfile, rectx, recty, "Black", svgtext, 10);
    free(svgtext);
}

void fg_report_in_svg_circles_inside_rects(type_svg svgfile, type_kdtree rects){
    if(empty_kdtree(rects)) return;
    CRV_svgfile = svgfile;

    // Creating a pointer to the function condition
    long(*always_true)(type_kdtitems);
    always_true = condition_true_aux; 

    // Creating a pointer to the function action
    void(*ptr_traverse_rects)(type_kdtitems);
    ptr_traverse_rects = fg_report_svg_action_aux;

    traverse_full_kdtree_with_conditional_action(rects, (void*)always_true, (void*)ptr_traverse_rects);
}



void print_one_node_rect_DEBUG(type_rect rect){
    char * id = get_rect_id(rect);
    printf("id_rect:[%s]\n", id);
}

void print_one_node_circle_DEBUG(type_circle circle){
    char * id = get_circle_id(circle);
    printf("id_circle:[%s]\n", id);
}

void print_rects_and_circles_DEBUG(type_kdtree rects, type_kdtree circles){
    if(empty_kdtree(rects) || empty_kdtree(circles)) return;
    // Creating a pointer to the function condition
    long(*ptr_true)(type_kdtitems);
    ptr_true = condition_true_aux;

    // Creating a pointer to the function action
    void(*ptr_print_rect)(type_kdtitems);
    ptr_print_rect = print_one_node_rect_DEBUG;

    // Creating a pointer to the function action
    void(*ptr_print_circle)(type_kdtitems);
    ptr_print_circle = print_one_node_circle_DEBUG;

    traverse_full_kdtree_with_conditional_action(rects, (void*)ptr_true, (void*)ptr_print_rect);
    traverse_full_kdtree_with_conditional_action(circles, (void*)ptr_true, (void*)ptr_print_circle);
}


