#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fg.h"

long(*FG_compare_circles)(type_circle, type_circle, int);
type_kdtree FG_circles;
type_kdtree FG_rects;
type_bstree FG_bstree;
type_circle FG_reference_circle;
type_circle FG_circle;
type_rect FG_mindist_rect;
double FG_mindist;

long fg_second_condition_aux(type_rect rect){
    // Checking if the building is active
    type_building building = get_rect_data(rect);
    if(!is_building_active(building)) return 0;

    // Comparing distance between rect and circle, to find the smallest one.
    double *centre = centre_of_mass_rect(rect);
    double circlex = get_circle_x(FG_circle);
    double circley = get_circle_y(FG_circle);
    double dist = distance_between_two_points(centre[0], centre[1], circlex, circley);
    free(centre);
    if(dist < FG_mindist){ 
        FG_mindist = dist; 
        return 1;
    }
    return 0;
}

void fg_second_action_aux(type_rect rect){
    // Saving minimum distance rect
    FG_mindist_rect = rect;
}

// Function that determines what side to traverse to for the fg function.
long fg_traverse_side_aux(type_circle circle, int axis){
    double pointx_max = get_circle_x(FG_reference_circle) + get_circle_radius(FG_reference_circle); 
    double pointy_max = get_circle_y(FG_reference_circle) + get_circle_radius(FG_reference_circle); 
    double pointx_min = get_circle_x(FG_reference_circle) - get_circle_radius(FG_reference_circle); 
    double pointy_min = get_circle_y(FG_reference_circle) - get_circle_radius(FG_reference_circle); 
    double dif_max = compare_circle_center_with_point(circle, pointx_max, pointy_max, axis);
    double dif_min = compare_circle_center_with_point(circle, pointx_min, pointy_min, axis);

    if(dif_max > 0) return 10;
    if(dif_min < 0) return 01;
    return 11;
}

long fg_condition_aux(type_circle circle){
    type_person person = get_circle_data(circle);
    return((long)circle_center_in_circle(FG_reference_circle, circle) && (long)is_person_alive(person) && (long)is_person_active(person));
}

long fg_action_aux(type_circle circle){
    double *centre, rand_number;
    char new_fill[30], new_stroke[30];
    type_circle new_circ;
    type_person person, cpyperson;

    // Setting value to other global variables used:      
    FG_circle = circle;
    FG_mindist_rect = NULL;
    FG_mindist = 9000000000000000; // just a big number!

    // Creating a pointer to the function condition for the second traverse
    long(*ptr_compare_minimum_dist)(type_kdtitems);
    ptr_compare_minimum_dist = fg_second_condition_aux;

    // Creating a pointer to the function action for the second traverse
    void(*ptr_save_minimum_dist_rect)(type_kdtitems);
    ptr_save_minimum_dist_rect = fg_second_action_aux;
    
    traverse_full_kdtree_with_conditional_action(FG_rects, (void*)ptr_compare_minimum_dist, (void*)ptr_save_minimum_dist_rect);
    
    if(FG_mindist_rect != NULL && !circle_center_in_rect(FG_mindist_rect, circle)){
        // Saving how many people went in the current building
        type_building building = get_rect_data(FG_mindist_rect);
        increase_amount_of_people_inside_building(building, 1);

        // Moving circle inside the centre of mass of the rect by creating a new circle and inserting it there
        // Creating a copy of the old circle
        person = get_circle_data(circle);
        new_circ = copy_circle(circle);
        cpyperson = copy_person(person);
        insert_data_in_circle(new_circ, cpyperson);

        // Changing it's coordinates
        centre = centre_of_mass_rect(FG_mindist_rect);
        rand_number = ((double)rand())/RAND_MAX;
        change_circle_x(new_circ, rand_number+centre[0]);
        change_circle_y(new_circ, rand_number+centre[1]);
        
        // And inserting it in the kdtree
        insert_item_in_kdtree(FG_circles, new_circ, 2, (void*)FG_compare_circles);

        // Deactivating old circle 
        change_person_active_status(person, 0);
        add_where_person_went(person, (double)(rand_number+centre[0]), (double)(rand_number+centre[1]));
        sprintf(new_fill, "LightGrey%c", '\0');
        sprintf(new_stroke, "Grey%c", '\0');        
        change_circle_fill_color(circle, new_fill);
        change_circle_stroke_color(circle, new_stroke);

        // Saving rectangle and circle id for the txt
        save_rectid_circleid_for_txt(FG_bstree, FG_mindist_rect, circle);
        free(centre);
    }
    return 0; 
}

void fg(type_circle reference_circle, type_kdtree circles, type_kdtree rects, type_txt txtfile){

    if(empty_kdtree(circles)) return;

    // Setting value to global variables used:
    FG_compare_circles = compare_circles_centers;
    FG_circles = circles;
    FG_rects = rects;
    FG_reference_circle = reference_circle;
    
    // Creating a binary search tree, in which data for the txtfile will be stored
    FG_bstree = create_binary_search_tree();

    srand((unsigned int)time(NULL));

    // Creating a pointer to the function that will decide with branches to visit
    long(*ptr_branch_decision)(type_kdtitems, int);
    ptr_branch_decision = fg_traverse_side_aux;

    // Creating a pointer to the function condition fg
    long(*ptr_circle_in_circle)(type_kdtitems);
    ptr_circle_in_circle = fg_condition_aux; 

    // Creating a pointer to the function action fg
    long(*ptr_traverse_rects)(type_kdtitems);
    ptr_traverse_rects = fg_action_aux;

    traverse_kdtree_with_conditional_action(circles, 2, (void*)ptr_branch_decision, (void*)ptr_circle_in_circle, (void*)ptr_traverse_rects);
    
    // Inserting in txt all the rectangle's and circle's id's stored previously
    insert_rectid_circleid_in_txt(FG_bstree, txtfile);
}

