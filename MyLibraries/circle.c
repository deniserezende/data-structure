//
//  circle.c
//  
//
//  Created by Denise F. de Rezende on 09/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circle.h"

typedef struct circle {
    char id[40];
    double radius;
    double x, y; //coordinates
    char stroke_color[30];
    char fill_color[30];
    type_circdata *data;
}CIRCLE;

type_circle new_circle(char id[], double x, double y, double r, char stroke[], char fill[]){
    CIRCLE *circle = malloc(sizeof(CIRCLE));

    sprintf(circle->id, "%s%c", id, '\0');
    circle->x = x;
    circle->y = y;
    circle->radius = r;
    sprintf(circle->stroke_color, "%s%c", stroke, '\0');
    sprintf(circle->fill_color, "%s%c", fill, '\0');
    circle->data = NULL;

    return(circle);
}

type_circle copy_circle(type_circle circle){
    CIRCLE *C = circle;
    CIRCLE *cpycircle = malloc(sizeof(CIRCLE));

    sprintf(cpycircle->id, "%s", C->id);
    cpycircle->x = C->x;
    cpycircle->y = C->y;
    cpycircle->radius = C->radius;
    sprintf(cpycircle->stroke_color, "%s", C->stroke_color);
    sprintf(cpycircle->fill_color, "%s", C->fill_color);
    cpycircle->data = NULL;

    return(cpycircle);
}


void destroi_circle(type_circle circle){
    CIRCLE *c = circle;
    free(c);
}

void insert_data_in_circle(type_circle circle, type_circdata data){
    CIRCLE *C = circle;
    C->data = data;
}

long compare_circles_centers(type_circle circle1, type_circle circle2, int axis){
    CIRCLE *C1 = circle1;
    CIRCLE *C2 = circle2;
    if(axis == 0){
        if((C1->x - C2->x) > 0.0) return 1;
        if((C1->x - C2->x) < 0.0) return -1;
        if((C1->x - C2->x) == 0.0) return 0;
    } 
    if((C1->y - C2->y) > 0.0) return 1;
    if((C1->y - C2->y) < 0.0) return -1;
    if((C1->y - C2->y) == 0.0) return 0;
    return 0;
}

long compare_circle_center_with_point(type_circle circle, double pointx, double pointy, int axis){
    CIRCLE *C = circle;
    if(axis == 0){
        if((C->x - pointx) > 0.0) return 1;
        if((C->x - pointx) < 0.0) return -1;
        if((C->x - pointx) == 0.0) return 0;
    } 
    if((C->y - pointy) > 0.0) return 1;
    if((C->y - pointy) < 0.0) return -1;
    if((C->y - pointy) == 0.0) return 0;
    return 0;
}

long compare_circles_by_id(type_circle circle1, type_circle circle2){
    CIRCLE *C1 = circle1;
    CIRCLE *C2 = circle2;

    if((strcmp(C1->id, C2->id)) > 0.0) return 1;
    if((strcmp(C1->id, C2->id)) < 0.0) return -1;
    if((strcmp(C1->id, C2->id)) == 0.0) return 0;
    return 0;
}    


char* get_circle_id(type_circle circle){
    CIRCLE *C = circle;
    return(C->id);
}

double get_circle_x(type_circle circle){
    CIRCLE *C = circle;
    return(C->x);
}

double get_circle_y(type_circle circle){
    CIRCLE *C = circle;
    return(C->y);
}

double get_circle_radius(type_circle circle){
    CIRCLE *C = circle;
    return(C->radius);
}

char* get_circle_stroke_color(type_circle circle){
    CIRCLE *C = circle;
    return(C->stroke_color);
}

char* get_circle_fill_color(type_circle circle){
    CIRCLE *C = circle;
    return(C->fill_color);
}

type_circdata get_circle_data(type_circle circle){
    CIRCLE *C = circle;
    return(C->data);
}

void change_circle_x(type_circle circle, double newx){
    CIRCLE *C = circle;
    C->x = newx;
}

void change_circle_y(type_circle circle, double newy){
    CIRCLE *C = circle;
    C->y = newy;
}

void change_circle_radius(type_circle circle, double new_radius){
    CIRCLE *C = circle;
    C->radius = new_radius;
}

void change_circle_fill_color(type_circle circle, char new_fill[]){
    CIRCLE *C = circle;
    strcpy(C->fill_color, "\0");
    sprintf(C->fill_color, "%s%c", new_fill, '\0');
}

void change_circle_stroke_color(type_circle circle, char new_stroke[]){
    CIRCLE *C = circle;
    strcpy(C->stroke_color, "\0");
    sprintf(C->stroke_color, "%s%c", new_stroke, '\0');
}

void change_circle_data(type_circle circle, type_circdata new_data){
    CIRCLE *C = circle;
    C->data = new_data;
}

