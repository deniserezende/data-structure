
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "im_t30_nve.h"

type_kdtree ITN_hsegments, ITN_vsegments;
type_bstree ITN_bstree;
type_segment ITN_segment_ptometeor;
type_meteor ITN_meteor;
double ITN_px, ITN_py;
double ITN_radiation_in_point;
double ITN_traverse_px, ITN_traverse_py;
int ITN_amount_intersections;

char* get_radiation_exposure_color(double radiation){
    char* color = malloc(sizeof(char) * 9);
    if(radiation < 25){
        sprintf(color, "#00ffff%c", '\0');
        return color;
    }
    if(25 <= radiation && radiation < 100){
        sprintf(color, "#00ff00%c", '\0');
        return color;
    }
    if(100 <= radiation && radiation < 150){
        sprintf(color, "#ff00ff%c", '\0'); 
        return color;
    }
    if(150 <= radiation && radiation < 250){
        sprintf(color, "#0000ff%c", '\0'); 
        return color;
    } 
    if(250 <= radiation && radiation < 500){
        sprintf(color, "#800080%c", '\0'); 
        return color;
    }
    if(500 <= radiation && radiation < 1000){
        sprintf(color, "#000080%c", '\0'); 
        return color;
    }
    if(1000 <= radiation && radiation < 8000){
        sprintf(color, "#ff0000%c", '\0'); 
        return color;
    }
    else{ //(8000 <= radiation)
        sprintf(color, "#000000%c", '\0');  
        return color;
    }
}

double calculate_radiation(double meteor_radiation, int amount){
    double new_radiation = meteor_radiation * pow(0.8, amount);
    return new_radiation;
}

void update_person_radiation(double meteor_radiation, type_person person, int amount){
    double current_radiation =  get_person_radiation_level(person);
    double new_radiation = calculate_radiation(meteor_radiation, amount);
    new_radiation = new_radiation + current_radiation;
    change_person_radiation_level(person, new_radiation);
}

void update_person_radiation_color(type_circle circle){
    type_person person = get_circle_data(circle);
    double radiation =  get_person_radiation_level(person);
    char* color = get_radiation_exposure_color(radiation);
    change_circle_fill_color(circle, color);
    free(color);
}

long intersection_of_segments_condition_aux(type_segment segment){
    double meteor_x = get_meteor_x(ITN_meteor);
    double meteor_y = get_meteor_y(ITN_meteor);
    return((long)!point_in_segment(segment, meteor_x, meteor_y) && (long)intersection_of_segments(segment, ITN_segment_ptometeor));
}

long intersection_of_segments_action_aux(type_segment segment){
    ITN_amount_intersections = ITN_amount_intersections + 1;
    return 0;
}

long traverse_hsegments_aux(type_segment segment, int axis){
    double meteor_x = get_meteor_x(ITN_meteor);
    double meteor_y = get_meteor_y(ITN_meteor);

    long difm = compare_segment_first_point_with_point(segment, meteor_x, meteor_y, axis);
    long difp = compare_segment_first_point_with_point(segment, ITN_traverse_px, ITN_traverse_py, axis);

    if(axis == 0){
        if(difm < 0 && difp < 0) return 10;
        else return 11;
    }
    else{
        if(difm < 0 && difp < 0) return 10;
        if(difm > 0 && difp > 0) return 01;
        else return 11;
    }
}

long traverse_vsegments_aux(type_segment segment, int axis){
    double meteor_x = get_meteor_x(ITN_meteor);
    double meteor_y = get_meteor_y(ITN_meteor);

    long difm = compare_segment_first_point_with_point(segment, meteor_x, meteor_y, axis);
    long difp = compare_segment_first_point_with_point(segment, ITN_traverse_px, ITN_traverse_py, axis);

    if(axis == 0){
        if(difm < 0 && difp < 0) return 10;
        if(difm > 0 && difp > 0) return 01;
        else return 11;
    }
    else{
        if(difm < 0 && difp < 0) return 10;
        else return 11;
    }
}

// Function im ------------------------------------------------------------------------------------

long im_condition_aux(type_circle circle){
    type_person person = get_circle_data(circle);
    return((long)is_person_alive(person) && (long)is_person_active(person));
}

void im_action_aux(type_circle circle){
    double circle_x = get_circle_x(circle);
    double circle_y = get_circle_y(circle);
    double meteor_x = get_meteor_x(ITN_meteor);
    double meteor_y = get_meteor_y(ITN_meteor);
    double meteor_radiation = get_meteor_radiation_level(ITN_meteor);
    double person_radiation;
    char* color = malloc(sizeof(char) * 8);
    type_person person = get_circle_data(circle);

    // Setting value to the global variables used:
    ITN_segment_ptometeor = new_segment_basic(circle_x, circle_y, meteor_x, meteor_y);
    ITN_amount_intersections = 0;  
    ITN_traverse_px = circle_x;
    ITN_traverse_py = circle_y;    

    // Creating a pointer to the function condition
    long(*ptr_check_intersection_segms)(type_litems);
    ptr_check_intersection_segms = intersection_of_segments_condition_aux; 

    // Creating a pointer to the function action
    long(*ptr_count_intersections)(type_litems);
    ptr_count_intersections = intersection_of_segments_action_aux;

    // Creating a pointer to the function traverse
    long(*ptr_traverse_hsegms)(type_litems, int);
    ptr_traverse_hsegms = traverse_hsegments_aux;

    // Creating a pointer to the function traverse
    long(*ptr_traverse_vsegms)(type_litems, int);
    ptr_traverse_vsegms = traverse_vsegments_aux;

    // Traversing both kdtrees of segments, horizontal and vertical.
    traverse_kdtree_with_conditional_action(ITN_hsegments, 2, (void*)ptr_traverse_hsegms, (void*)ptr_check_intersection_segms, (void*)ptr_count_intersections);
    traverse_kdtree_with_conditional_action(ITN_vsegments, 2, (void*)ptr_traverse_vsegms, (void*)ptr_check_intersection_segms, (void*)ptr_count_intersections);

    // Updating person radiation and color based on current radiation
    update_person_radiation(meteor_radiation, person, ITN_amount_intersections);
    update_person_radiation_color(circle);

    // Checking if radiation is more than 1000 -> death is imminent.
    person_radiation = get_person_radiation_level(person);
    if(person_radiation >= 1000){
        save_circleid_for_txt(ITN_bstree, circle);
        // Checking if radiation is more than 8000 -> death.
        if(person_radiation >= 8000){
            sprintf(color,"Black%c", '\0');
            change_circle_fill_color(circle, color);
            change_circle_stroke_color(circle, color);
            change_person_alive_status(person, 0);    
        }
    } 

}

void im(type_meteor meteor, type_kdtree circles, type_kdtree hsegments, type_kdtree vsegments, type_txt txtfile){
    if(empty_kdtree(circles)) return;

    // Setting value to global variables used:
    ITN_hsegments = hsegments;    
    ITN_vsegments = vsegments;    
    ITN_meteor = meteor;

    // Creating a binary search tree, in which data for the txtfile will be stored
    ITN_bstree = create_binary_search_tree();

    // Creating a pointer to the function 'condition', to check is the person is alive
    long(*ptr_check_person_condition)(type_kdtitems);
    ptr_check_person_condition = im_condition_aux; 

    // Creating a pointer to the function 'action', in which we will do another traverse
    void(*ptr_traverse_segments)(type_kdtitems);
    ptr_traverse_segments = im_action_aux;
    
    traverse_full_kdtree_with_conditional_action(circles, (void*)ptr_check_person_condition, (void*)ptr_traverse_segments);

    // Inserting in txt all the circle's id's stored previously
    insert_circleid_in_txt(ITN_bstree, txtfile);
}

// Function nve ------------------------------------------------------------------------------------

long nve_condition_aux(type_meteor meteor){
    return 1;
}

long nve_action_aux(type_meteor meteor){
    double meteor_x = get_meteor_x(meteor);
    double meteor_y = get_meteor_y(meteor);
    double meteor_radiation = get_meteor_radiation_level(meteor);    

    // Setting value to the global variables used:
    ITN_meteor = meteor;
    ITN_segment_ptometeor = new_segment_basic(meteor_x, meteor_y, ITN_px, ITN_py);
    ITN_amount_intersections = 0;        

    // Creating a pointer to the function condition
    long(*ptr_check_intersection_segms)(type_litems);
    ptr_check_intersection_segms = intersection_of_segments_condition_aux; 

    // Creating a pointer to the function action
    long(*ptr_count_intersections)(type_litems);
    ptr_count_intersections = intersection_of_segments_action_aux;

    // Creating a pointer to the function traverse
    long(*ptr_traverse_hsegms)(type_litems, int);
    ptr_traverse_hsegms = traverse_hsegments_aux;

    // Creating a pointer to the function traverse
    long(*ptr_traverse_vsegms)(type_litems, int);
    ptr_traverse_vsegms = traverse_vsegments_aux;

    if(!empty_kdtree(ITN_hsegments)) traverse_kdtree_with_conditional_action(ITN_hsegments, 2, (void*)ptr_traverse_hsegms, (void*)ptr_check_intersection_segms, (void*)ptr_count_intersections);
    if(!empty_kdtree(ITN_vsegments)) traverse_kdtree_with_conditional_action(ITN_vsegments, 2, (void*)ptr_traverse_vsegms, (void*)ptr_check_intersection_segms, (void*)ptr_count_intersections);
    ITN_radiation_in_point = ITN_radiation_in_point + calculate_radiation(meteor_radiation, ITN_amount_intersections);
    return 0;
}

double nve(double point_x, double point_y, type_list meteors, type_kdtree hsegments, type_kdtree vsegments, type_txt txtfile){
    if(empty_list(meteors)) return 0;

    // Setting value to the global variables used:
    ITN_hsegments = hsegments;    
    ITN_vsegments = vsegments;  
    ITN_px = point_x;
    ITN_py = point_y;
    ITN_traverse_px = point_x;
    ITN_traverse_py = point_y;  
    ITN_radiation_in_point = 0;

    // Creating a pointer to the function condition
    long(*ptr_true)(type_litems);
    ptr_true = nve_condition_aux; 

    // Creating a pointer to the function action
    long(*ptr_count_intersections)(type_litems);
    ptr_count_intersections = nve_action_aux;

    traverse_full_list_with_conditional_action(meteors, (void*)ptr_true,  (void*)ptr_count_intersections);

    // Inserting radiation in point in txtfile
    char *stringtxt = malloc(sizeof(char) * 15);
    sprintf(stringtxt, "%f%c", ITN_radiation_in_point, '\0');
    insert_string_in_txt(txtfile, stringtxt);
    free(stringtxt);

    return ITN_radiation_in_point;
}

// Function t30 ------------------------------------------------------------------------------------

long t30_condition_aux(type_circle circle){
    // Checking person status 
    type_person person = get_circle_data(circle);
    if(!is_person_alive(person) || !is_person_active(person)) return 0;
    
    // Checking if person radiation level is indicator of imminent death.
    double radiation = get_person_radiation_level(person);
    return((long)(radiation > 1000 && radiation < 8000));
}

void t30_action_aux(type_circle circle){
    // Changing person alive status
    type_person person = get_circle_data(circle);
    char *color = malloc(sizeof(char) * 8);
    sprintf(color, "Black%c", '\0');
    change_person_alive_status(person, 0);
    change_circle_fill_color(circle, color);
    change_circle_stroke_color(circle, color);

    // Saving circle id for txt
    save_circleid_for_txt(ITN_bstree, circle);
    free(color);
}

void t30(type_kdtree circles, type_txt txtfile){
    if(empty_kdtree(circles)) return;    
    
    // Creating a binary search tree, in which data for the txtfile will be stored
    ITN_bstree = create_binary_search_tree();

    // Creating a pointer to the function t30 condition
    long(*ptr_check_person_radiation)(type_kdtitems);
    ptr_check_person_radiation = t30_condition_aux; 

    // Creating a pointer to the function t30 action
    void(*ptr_person_dead)(type_kdtitems);
    ptr_person_dead = t30_action_aux;

    traverse_full_kdtree_with_conditional_action(circles, (void*)ptr_check_person_radiation, (void*)ptr_person_dead);

    // Inserting in txt all the circle's id's stored previously
    insert_circleid_in_txt(ITN_bstree, txtfile);
}














