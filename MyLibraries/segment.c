//
//  segment.c
//  
//
//  Sreated by Denise F. de Rezende on 10/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segment.h"

typedef struct segment {
    char id[40];
    double x, y; //coordinates
    double x2, y2;
    char stroke_color[30];
    type_segdata *data;
}SEGMENT;

type_segment new_segment(char id[], double x, double y, double x2, double y2, char stroke[]){
    SEGMENT *seg = malloc(sizeof(SEGMENT));

    sprintf(seg->id, "%s%c", id, '\0');
    seg->x = x;
    seg->y = y;
    seg->x2 = x2;
    seg->y2 = y2;
    sprintf(seg->stroke_color, "%s%c", stroke, '\0');
    seg->data = NULL;

    return(seg);
}

type_segment new_segment_basic(double x, double y, double x2, double y2){
    SEGMENT *seg = malloc(sizeof(SEGMENT));

    sprintf(seg->id, "%c",'\0');
    seg->x = x;
    seg->y = y;
    seg->x2 = x2;
    seg->y2 = y2;
    sprintf(seg->stroke_color, "%c", '\0');
    seg->data = NULL;

    return(seg);
}

type_segment copy_segment_basic(type_segment segment){
    SEGMENT *seg = segment;
    SEGMENT *cpyseg = malloc(sizeof(SEGMENT));

    sprintf(cpyseg->id, "%c",'\0');
    cpyseg->x = seg->x;
    cpyseg->y = seg->y;
    cpyseg->x2 = seg->x2;
    cpyseg->y2 = seg->y2;
    sprintf(cpyseg->stroke_color, "%c", '\0');
    cpyseg->data = NULL;

    return(cpyseg);
}

long compare_segments_by_first_point(type_segment segment1, type_segment segment2, int axis){
    SEGMENT *S1 = segment1;
    SEGMENT *S2 = segment2;
    if(axis == 0){
        if((S1->x - S2->x) > 0.0) return 1;
        if((S1->x - S2->x) < 0.0) return -1;
        if((S1->x - S2->x) == 0.0) return 0;
    } 
    if((S1->y - S2->y) > 0.0) return 1;
    if((S1->y - S2->y) < 0.0) return -1;
    if((S1->y - S2->y) == 0.0) return 0;
    return 0;
}


long compare_segment_first_point_with_point(type_segment segment, double pointx, double pointy, int axis){
    SEGMENT *S = segment;
    if(axis == 0){
        if((S->x - pointx) > 0.0) return 1;
        if((S->x - pointx) < 0.0) return -1;
        if((S->x - pointx) == 0.0) return 0;
    } 
    if((S->y - pointy) > 0.0) return 1;
    if((S->y - pointy) < 0.0) return -1;
    if((S->y - pointy) == 0.0) return 0;
    return 0;
}

void destroi_segment(type_segment segment){
    SEGMENT *seg = segment;
    free(seg);
}


void insert_data_in_segment(type_segment segment, type_segdata data){
    SEGMENT *seg = segment;
    seg->data = data;
}


char* get_segment_id(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->id);
}

double get_segment_first_x(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->x);
}

double get_segment_first_y(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->y);
}

double get_segment_second_x(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->x2);
}

double get_segment_second_y(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->y2);
}

char* get_segment_stroke_color(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->stroke_color);
}

type_segdata get_segment_data(type_segment segment){
    SEGMENT *seg = segment;
    return(seg->data);
}

void change_segment_first_x(type_segment segment, double newx){
    SEGMENT *seg = segment;
    seg->x = newx;
}

void change_segment_first_y(type_segment segment, double newy){
    SEGMENT *seg = segment;
    seg->y = newy;
}


void change_segment_second_x(type_segment segment, double newx2){
    SEGMENT *seg = segment;
    seg->x2 = newx2;
}

void change_segment_second_y(type_segment segment, double newy2){
    SEGMENT *seg = segment;
    seg->y2 = newy2;
}

void change_segment_stroke_color(type_segment segment, char new_stroke[]){
    SEGMENT *seg = segment;
    strcpy(seg->stroke_color, "\0");
    sprintf(seg->stroke_color, "%s%c", new_stroke, '\0');
}

void change_segment_data(type_segment segment, type_segdata new_data){
    SEGMENT *seg = segment;
    seg->data = new_data;
}


