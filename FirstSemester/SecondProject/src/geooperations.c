//
//  geooperations.c
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geooperations.h"



void read_geo_and_saves_info(char *filename, type_kdtree *circle_kdtree, type_kdtree *rect_kdtree){
    FILE *geofile = fopen(filename, "r");
    if(geofile == NULL){
        return;
    }

    char *line = malloc(80 * sizeof(char));
    char *helper = malloc(3 *sizeof(char));
    char id_rect[40], id_circle[40];
    char stroke_rect[30], fill_rect[30];
    char stroke_circle[30], fill_circle[30];
    char stroke_old_rect[30], fill_old_rect[30];
    char stroke_old_circle[30], fill_old_circle[30];
    double x_rect, y_rect, w_rect, h_rect, x_circle, y_circle, r_circle;
    type_rect rect;
    type_circle circle;
    type_person person;
    type_building building;

    // Creating a pointer to the function 
    long(*compare_circles)(type_circle, type_circle, int);
    compare_circles = compare_circles_centers;
    
    // Creating a pointer to the function
    long(*compare_rects)(type_rect, type_rect, int);
    compare_rects = compare_rectangles_by_reference_point;

    while(!feof(geofile)){
        fscanf(geofile, "\n%[^\n]s\n", line);
        
        if(strncmp(line, "cc", 2) == 0){
            memset(stroke_old_rect, '\0', sizeof(stroke_old_rect));
            memcpy(stroke_old_rect, line + 3, strlen(line) - 3);
        }
        else if(strncmp(line, "cp", 2) == 0){
                memset(fill_old_rect, 0, sizeof(fill_old_rect));
                memcpy(fill_old_rect, line + 3, strlen(line) - 3);
            }
            else if(strncmp(line, "r", 1) == 0){
                    sscanf(line, "%s %s %lf %lf %lf %lf", helper, id_rect, &x_rect, &y_rect, &w_rect, &h_rect);
                    strcpy(stroke_rect, stroke_old_rect);
                    strcpy(fill_rect, fill_old_rect);
                    rect = new_rectangle(id_rect, x_rect, y_rect, w_rect, h_rect, stroke_rect, fill_rect);
                    building = new_building(1, 0);
                    insert_data_in_rect(rect, building); 
                    insert_item_in_kdtree(*rect_kdtree, rect, 2, (void*)compare_rects);
                }
                else if(strncmp(line, "bc", 2) == 0){
                        memset(stroke_old_circle, 0, sizeof(stroke_old_circle));
                        memcpy(stroke_old_circle, line + 3, strlen(line) - 3);
                    }
                    else if(strncmp(line, "pc", 2) == 0){
                            memset(fill_old_circle, 0, sizeof(fill_old_circle));
                            memcpy(fill_old_circle, line + 3, strlen(line) - 3);
                        }
                        else if(strncmp(line, "c ", 2) == 0){
                                sscanf(line, "%s %s %lf %lf %lf", helper, id_circle, &x_circle, &y_circle, &r_circle);
                                strcpy(stroke_circle, stroke_old_circle);
                                strcpy(fill_circle, fill_old_circle);
                                circle = new_circle(id_circle, x_circle, y_circle, r_circle, stroke_circle, fill_circle);
                                person = new_person(0, 1, 1);
                                insert_data_in_circle(circle, person);
                                insert_item_in_kdtree(*circle_kdtree, circle, 2, (void*)compare_circles);
                            }
                            else if(strncmp(line, "nx", 2) == 0){
                                // No need to do anything, because I don't use this data!
                                }
                                else break;
        // "Resets" the string
        strcpy(line, "\0");
    }

    free(line);
    free(helper);
    fclose(geofile);
}


