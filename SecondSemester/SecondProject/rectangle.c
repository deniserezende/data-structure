//
//  rectangle.c
//  
//
//  Created by Denise F. de Rezende on 25/05/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rectangle.h"

typedef struct rectangle{
    char id[40];
    double width, height;
    double x, y; //coordinates
    char stroke_color[30];
    char fill_color[30];
    double stroke_width;
    type_rectdata *data;
}RECT;

type_rect new_rectangle(char id[], double x, double y, double w, double h, char stroke[], char fill[]){
    RECT *rect = malloc(sizeof(RECT));

    sprintf(rect->id, "%s", id);
    rect->x = x;
    rect->y = y;
    rect->width = w;
    rect->height = h;
    sprintf(rect->stroke_color, "%s", stroke);
    sprintf(rect->fill_color, "%s", fill);
    rect->data = NULL;

    return(rect);
}

void add_rectangles_stroke_width(type_rect rectangle, double stroke_width){
    RECT *rect = rectangle;
    rect->stroke_width = stroke_width;
}


type_rect copy_rectangle(type_rect rectangle){
    RECT *rect = rectangle;
    RECT *cpyrect = malloc(sizeof(RECT));

    sprintf(cpyrect->id, "%s", rect->id);
    cpyrect->x = rect->x;
    cpyrect->y = rect->y;
    cpyrect->width = rect->width;
    cpyrect->height = rect->height;
    sprintf(cpyrect->stroke_color, "%s", rect->stroke_color);
    sprintf(cpyrect->fill_color, "%s", rect->fill_color);
    cpyrect->data = NULL;

    return(cpyrect);
}

void destroi_rectangle(type_rect rectangle){
    RECT *rect = rectangle;
    free(rect);
}

void insert_data_in_rect(type_rect rectangle, type_rectdata data){
    RECT *rect = rectangle;
    rect->data = data;
}


long compare_rectangles_by_x_coordinate(type_rect rectangle1, type_rect rectangle2){
    RECT *rect1 = rectangle1;
    RECT *rect2 = rectangle2;

    if((rect1->x - rect2->x) > 0.0) return 1;
    if((rect1->x - rect2->x) < 0.0) return -1;
    else return 0;
}

// 0 = x
// 1 = y
long compare_rectangles_by_reference_point(type_rect rectangle1, type_rect rectangle2, int axis){
    RECT *rect1 = rectangle1;
    RECT *rect2 = rectangle2;
    if(axis == 0){
        if((rect1->x - rect2->x) > 0.0) return 1;
        if((rect1->x - rect2->x) < 0.0) return -1;
        if((rect1->x - rect2->x) == 0.0) return 0;
    } 
    if((rect1->y - rect2->y) > 0.0) return 1;
    if((rect1->y - rect2->y) < 0.0) return -1;
    if((rect1->y - rect2->y) == 0.0) return 0;
    return 0;
}

long compare_rectangle_reference_point_with_point(type_rect rectangle, double pointx, double pointy, int axis){
    RECT *rect = rectangle;
    if(axis == 0){
        if((rect->x - pointx) > 0.0) return 1;
        if((rect->x - pointx) < 0.0) return -1;
        if((rect->x - pointx) == 0.0) return 0;
    } 
    if((rect->y - pointy) > 0.0) return 1;
    if((rect->y - pointy) < 0.0) return -1;
    if((rect->y - pointy) == 0.0) return 0;
    return 0;
}

long compare_rectangles_by_id(type_rect rectangle1, type_rect rectangle2){
    RECT *rect1 = rectangle1;
    RECT *rect2 = rectangle2;

    if((strcmp(rect1->id, rect2->id)) > 0.0) return 1;
    if((strcmp(rect1->id, rect2->id)) < 0.0) return -1;
    if((strcmp(rect1->id, rect2->id)) == 0.0) return 0;
    return 0;
}

int check_if_id_match_rects(type_rect rectangle, char *name){
    RECT *rect = rectangle;
    if(memcmp(name, rect->id, strlen(rect->id)) == 0){
        return 1;
    }
    return 0;
}

int check_if_rects_ids_match(type_rect rectangle1, type_rect rectangle2){
    RECT *rect1 = rectangle1;
    RECT *rect2 = rectangle2;
    if(memcmp(rect2->id, rect1->id, strlen(rect1->id)) == 0){
        return 1;
    }
    return 0;
}

char* get_rect_id(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->id);
}

double get_rect_x(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->x);
}

double get_rect_y(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->y);
}

double get_rect_width(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->width);
}

double get_rect_height(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->height);
}

char* get_rect_stroke_color(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->stroke_color);
}

char* get_rect_fill_color(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->fill_color);
}

type_rectdata get_rect_data(type_rect rect){
    RECT *rectangle = rect;
    return(rectangle->data);
}

void change_rect_x(type_rect rect, double newx){
    RECT *rectangle = rect;
    rectangle->x = newx;
}

void change_rect_y(type_rect rect, double newy){
    RECT *rectangle = rect;
    rectangle->y = newy;
}

void change_rect_width(type_rect rect, double new_width){
    RECT *rectangle = rect;
    rectangle->width = new_width;
}

void change_rect_height(type_rect rect, double new_height){
    RECT *rectangle = rect;
    rectangle->height = new_height;
}

void change_rect_fill_color(type_rect rect, char *new_fill){
    RECT *rectangle = rect;
    strcpy(rectangle->fill_color, "\0");
    strcpy(rectangle->fill_color, new_fill);
}

void change_rect_stroke_color(type_rect rect, char *new_stroke){
    RECT *rectangle = rect;
    strcpy(rectangle->stroke_color, "\0");
    strcpy(rectangle->stroke_color, new_stroke);
}

void change_rect_data(type_rect rect, type_rectdata new_data){
    RECT *rectangle = rect;
    rectangle->data = new_data;
}
