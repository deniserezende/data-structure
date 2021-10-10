//
//  qryoperations.c 
//  
//
//  Created by Denise F. de Rezende on 25/05/21.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "qryoperations.h"

// Global variable only used to create list of segments:
type_kdtree sr_hsegments; // horizontal segments
type_kdtree sr_vsegments; // vertical segments

// Global variables only used to find rectangle:
type_rect fr_rect;
char fr_name[40];

/* AUXILIARY FUNCTIONS PROTOTYPE */
type_rect find_rectangle(type_kdtree rects, char *name);
void insert_rects_segments_in_kdtrees(type_kdtree rects, type_kdtree horizontal_segments, type_kdtree vertical_segments);
void destroi_segments(type_kdtree hsegments, type_kdtree vsegments);
void destroi_rectangles(type_kdtree rects);
void destroi_circles(type_kdtree circles);

void read_qry_and_report_called_functions(char *qryfilename, type_txt txtfile, type_svg svgfile, type_kdtree rects, type_kdtree circles){
    FILE *qryfile = fopen(qryfilename, "r");
    if (qryfile == NULL) {
        return;
    }
    char *line = malloc(60 * sizeof(char));
    char *helper = malloc(5 * sizeof(char));
    char *rectname = malloc(40 * sizeof(char));
    char *point_radiation_str = malloc(sizeof(char) * 15);
    char *radiation_color;
    char fill[30], stroke[30];
    double x, y, w, h, r, s, point_radiation;
    int needs_to_report_fg = 0;
    type_rect rect_refer = NULL;
    type_circle reference_circle;
    type_list meteors = create_list();

    int inserted_segments = 0;
    type_kdtree hsegments = create_kdtree(2);
    type_kdtree vsegments = create_kdtree(2);

    while(!feof(qryfile)){ 
        fscanf(qryfile, "\n%[^\n]\ns", line);

        if(strncmp(line, "dpi", 3) == 0){
            insert_string_in_txt(txtfile, "dpi");
            sscanf(line, "%s %lf %lf", helper, &x, &y);
            dpi(rects, x, y, txtfile);
        }
        else if(strncmp(line, "dr", 2) == 0){
                insert_string_in_txt(txtfile, "dr");
                sscanf(line, "%s %s", helper, rectname);
                rect_refer = find_rectangle(rects, rectname);
                if(rect_refer == NULL){
                    printf("The id given is not in the list.\n");
                }
                else dr(rects, rect_refer, txtfile);
            }
            else if(strncmp(line, "fg", 2) == 0 || strncmp(line, "fg\0", 3) == 0){
                    insert_string_in_txt(txtfile, "fg"); 
                    sscanf(line, "%s %lf %lf %lf", helper, &x, &y, &r);
                    
                    // Inserting reference rect in svg
                    sprintf(stroke, "red%c", '\0');
                    sprintf(fill, "transparent%c", '\0');
                    reference_circle =  new_circle("\0", x, y, r, stroke, fill);
                    insert_circle_in_svg(svgfile, x, y, r, fill, stroke, 1);

                    fg(reference_circle, circles, rects, txtfile);
                    needs_to_report_fg = 1;
                }
                else if(strncmp(line, "im", 2) == 0){
                        insert_string_in_txt(txtfile, "im");
                        sscanf(line, "%s %lf %lf %lf", helper, &x, &y, &s);
                        
                        // Creating new meteor and inserting it in the list of meteors
                        type_meteor meteor = new_meteor(x, y, s);
                        insert_item_at_the_end_of_list(meteors, meteor);

                        if(!inserted_segments){
                            insert_rects_segments_in_kdtrees(rects, hsegments, vsegments);
                            inserted_segments = 1;
                        }
                        im(meteor, circles, hsegments, vsegments, txtfile);
                    }
                    else if(strncmp(line, "t30 ", 3) == 0){
                            insert_string_in_txt(txtfile, "t30");
                            t30(circles, txtfile);
                        }
                        else if(strncmp(line, "nve", 3) == 0){
                                sscanf(line, "%s %lf %lf", helper, &x, &y);
                                insert_string_in_txt(txtfile, "nve");
                                
                                point_radiation = nve(x, y, meteors, hsegments, vsegments, txtfile);                                
                                
                                radiation_color = get_radiation_exposure_color(point_radiation);
                                insert_rectangle_with_rounded_corners_in_svg(svgfile, x, y, 5, 5,  1, 1, radiation_color, radiation_color, 2);
                                sprintf(point_radiation_str, "%f%c", point_radiation, '\0');
                                insert_text_in_svg(svgfile, x, y, "Black", point_radiation_str, 10);
                                
                                free(radiation_color);
                            }
  
        // "Resets" the string
        strcpy(line, "\0");
    }

    insert_active_rects_in_svg(svgfile, rects);
    insert_circles_considering_status_in_svg(svgfile, circles);
    insert_meteors_in_svg(svgfile, meteors);
    if(needs_to_report_fg) fg_report_in_svg_circles_inside_rects(svgfile, rects);

    destroi_rectangles(rects);
    destroi_circles(circles);
    if(inserted_segments) destroi_segments(hsegments, vsegments);

    free(line);
    free(helper);
    free(rectname);
    free(point_radiation_str);
    fclose(qryfile);
}
/* ------------------------------------- AUXILIARY FUNCTIONS QRY --------------------------------------------*/




// FIND RECTANGLE --------------------------------------------------------------------------------------------
// type_rect fr_rect and char fr_name[40] are global variables only used here!
long fr_condition_aux(type_rect rect){
    return((long)check_if_id_match_rects(rect, fr_name));
}
void fr_action_aux(type_rect rect){
    fr_rect = rect;
}

type_rect find_rectangle(type_kdtree rects, char *name){
    fr_rect = NULL;
    strcpy(fr_name, name);
    
    // Pointer to the condition of the traverse: check if id given matches rects id.
    long(*ptr_id_match)(type_rect);
    ptr_id_match = fr_condition_aux;
    
    // Pointer to the action of the traverse: saving rect.
    void(*ptr_get_rect)(type_rect);
    ptr_get_rect = fr_action_aux;
    
    traverse_kdtree_until_condition_is_met_then_take_action(rects, (void*)ptr_id_match, (void*)ptr_get_rect);
    return fr_rect;
}
// END FIND RECTANGLE ----------------------------------------------------------------------------------------


// SEPARATE RECTANGLE IN SEGMENTS ---------------------------------------------------------------------------------
// sr_hsegments and sr_vsegments are global variables only used here!
void save_rects_segm_action_aux(type_rect rect){
    double x = get_rect_x(rect);
    double y = get_rect_y(rect);
    double w = get_rect_width(rect);
    double h = get_rect_height(rect);
    type_segment segmenth1 = NULL, segmenth2 = NULL, segmentv1 = NULL , segmentv2 = NULL;
    segmenth1 = new_segment_basic(x, y, x+w, y); // horizontal
    segmentv1 = new_segment_basic(x+w, y, x+w, y+h); // vertical
    segmenth2 = new_segment_basic(x, y+h, x+w, y+h); // horizontal
    segmentv2 = new_segment_basic(x, y, x, y+h); // vertical

    long(*ptr_compare)(type_kdtitems, type_kdtitems, int);
    ptr_compare = compare_segments_by_first_point;

    insert_item_in_kdtree(sr_hsegments, segmenth1, 2, (void*)ptr_compare);
    insert_item_in_kdtree(sr_hsegments, segmenth2, 2, (void*)ptr_compare);
    insert_item_in_kdtree(sr_vsegments, segmentv1, 2, (void*)ptr_compare);
    insert_item_in_kdtree(sr_vsegments, segmentv2, 2, (void*)ptr_compare);
}

long save_rects_segm_condition_aux(type_rect rect){
    type_building building = get_rect_data(rect); 
    if(is_building_active(building)) return 1;
    return 0;
}

void insert_rects_segments_in_kdtrees(type_kdtree rects, type_kdtree horizontal_segments, type_kdtree vertical_segments){
    // Global variable set here.
    sr_hsegments = horizontal_segments;
    sr_vsegments = vertical_segments;

    if(empty_kdtree(rects)) return;

    // Creating a pointer to the function 'condition', checking whether a building is active
    long(*ptr_check_active_building)(type_kdtitems);
    ptr_check_active_building = save_rects_segm_condition_aux; 

    // Creating a pointer to the function 'action', separating rectangles in to segments and adding them to a list 
    void(*ptr_save_segs_to_list)(type_kdtitems);
    ptr_save_segs_to_list = save_rects_segm_action_aux;

    traverse_full_kdtree_with_conditional_action(rects, (void*)ptr_check_active_building, (void*)ptr_save_segs_to_list);
}
// END SEPARATE RECTANGLE IN SEGMENTS ------------------------------------------------------------------------------

void destroi_segments(type_kdtree hsegments, type_kdtree vsegments){
    void(*ptr_destroi_segment)(type_segment);
    ptr_destroi_segment = destroi_segment;

    destroi_kdtree(hsegments, 2, (void*)ptr_destroi_segment);
    destroi_kdtree(vsegments, 2, (void*)ptr_destroi_segment);
}

void destroi_rectangles(type_kdtree rects){
    void(*ptr_destroi_rect)(type_rect);
    ptr_destroi_rect = destroi_rectangle;

    destroi_kdtree(rects, 2, (void*)ptr_destroi_rect);

}

void destroi_circles(type_kdtree circles){
    void(*ptr_destroi_circle)(type_circle);
    ptr_destroi_circle = destroi_circle;

    destroi_kdtree(circles, 2, (void*)ptr_destroi_circle);
}


