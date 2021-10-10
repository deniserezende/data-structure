
#include <stdio.h>
#include "dpi_dr.h"

long(*D_compare_rects)(type_rect, type_rect, int);
type_kdtree D_rects;
type_bstree D_bstree;
type_rect DR_reference_rect;
double DPI_px, DPI_py;

// Function that determines what side to traverse to for the dpi function.
long dpi_traverse_side_aux(type_rect rect, int axis){
    long dif = compare_rectangle_reference_point_with_point(rect, DPI_px, DPI_py, axis);
    // Axis x
    if(axis == 0){
        if(dif > 0) return 10;
        else return 11;
    }
    // Aixis y
    else{
        if(dif < 0) return 01;
        else return 11;
    }
}

long dpi_condition_aux(type_rect rect){
    type_building building = get_rect_data(rect);
    return((long)is_building_active(building) && (long)point_in_rect(rect, DPI_px, DPI_py));
}

long dpi_and_dr_action_aux(type_rect rect){
    char new_fill[30], new_stroke[30];
    char *rectid = get_rect_id(rect);

    // Deactivating building (rectangle)
    type_building building = get_rect_data(rect);
    change_if_building_is_active(building, 0);
    sprintf(new_fill, "transparent%c", '\0');
    sprintf(new_stroke, "transparent%c", '\0');
    change_rect_fill_color(rect, new_fill);
    change_rect_stroke_color(rect, new_stroke);

    // Saving rectangle id for the txt output file
    save_rectid_for_txt(D_bstree, rect);
    return 0;
}

void dpi(type_kdtree rects, float px, float py, type_txt txtfile){

    // Setting value to global variables used:
    D_compare_rects = compare_rectangles_by_reference_point;
    D_rects = rects;
    DPI_px = px;
    DPI_py = py;

    // Creating a binary search tree, in which data for the txtfile will be stored
    D_bstree = create_binary_search_tree();

    // Creating a pointer to the function that will decide which branches to visit
    long(*ptr_branch_decision)(type_kdtitems, int);
    ptr_branch_decision = dpi_traverse_side_aux;

    // Creating a pointer to the function condition dpi
    long(*ptr_point_in_rect)(type_kdtitems);
    ptr_point_in_rect = dpi_condition_aux;

    // Creating a pointer to the function action dpi
    long(*ptr_remove_rect)(type_kdtitems);
    ptr_remove_rect = dpi_and_dr_action_aux;

    traverse_kdtree_with_conditional_action(rects, 2, (void*)ptr_branch_decision, (void*)ptr_point_in_rect, (void*)ptr_remove_rect);

    // Inserting in txt all the rectangle's id's stored previously
    insert_rectid_in_txt(D_bstree, txtfile);
}



// Function that determines what side to traverse to for the dr function.
long dr_traverse_side_aux(type_rect rect, int axis){
    long dif = compare_rectangles_by_reference_point(rect, DR_reference_rect, axis);
    // Axis x
    if(axis == 0){
        if(dif < 0) return 01;
        else return 11;
    }
    // Axis y
    else{
        if(dif > 0) return 10;
        else return 11;
    }
}

long dr_condition_aux(type_rect rect){
    type_building building = get_rect_data(rect);
    return((long)is_building_active(building) && (long)rect_in_rect(DR_reference_rect, rect) && (long)!check_if_rects_ids_match(DR_reference_rect, rect));
}

void dr(type_kdtree rects, type_rect reference_rect, type_txt txtfile){
    // Setting value to global variables used:
    D_compare_rects = compare_rectangles_by_reference_point;
    D_rects = rects;
    DR_reference_rect = reference_rect;

    // Creating a binary search tree, in which data for the txtfile will be stored
    D_bstree = create_binary_search_tree();

    // Creating a pointer to the function that will decide which branches to visit
    long(*ptr_branch_decision)(type_kdtitems, int);
    ptr_branch_decision = dr_traverse_side_aux;

    // Creating a pointer to the function condition dr
    long(*ptr_rect_in_rect)(type_kdtitems);
    ptr_rect_in_rect = dr_condition_aux;

    // Creating a pointer to the function action dr
    long(*ptr_remove_rect)(type_kdtitems);
    ptr_remove_rect = dpi_and_dr_action_aux;

    traverse_kdtree_with_conditional_action(rects, 2, (void*)ptr_branch_decision , (void*)ptr_rect_in_rect, (void*)ptr_remove_rect);

    // Inserting in txt all the rectangle's id's stored previously
    insert_rectid_in_txt(D_bstree, txtfile);
}








