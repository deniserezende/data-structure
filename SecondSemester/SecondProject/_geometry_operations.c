// 
//  geometry_operations.c
//  
//
//  Created by Denise F. de Rezende on 15/06/21.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "_geometry_operations.h"

// Note that: this function returns 1 if the point is inside the rect or in it's border.
int point_in_rect(type_rect rect, double px, double py){
    double rectx = get_rect_x(rect);
    double recty = get_rect_y(rect);
    double rectwidth = get_rect_width(rect);
    double rectheight = get_rect_height(rect);
    if((rectx <= px) && px <= (rectx + rectwidth)){
        if((recty <= py) && py <= (recty + rectheight)){
            return 1;
        }
    }
    return 0;
}

// Note that: if the rectangles are exactly the same the function considers one inside the other.
int rect_in_rect(type_rect reference_rect, type_rect second_rect){
    double srectx = get_rect_x(second_rect);
    double srectwidth = get_rect_width(second_rect);
    double srecty = get_rect_y(second_rect);
    double srectheight = get_rect_height(second_rect);
    if(point_in_rect(reference_rect, srectx, srecty) && point_in_rect(reference_rect, (srectx + srectwidth), (srecty + srectheight))){
        return 1;
    }
    return 0;
}

// Note that: the reference point of the rectangle has to be the lowest x and y.
double* centre_of_mass_rect(type_rect rect){
    double x = get_rect_x(rect);
    double y = get_rect_y(rect);
    double w = get_rect_width(rect);
    double h = get_rect_height(rect);
    double *centre = malloc(2*sizeof(double));
    centre[0] = x + (w/2);
    centre[1] = y + (h/2); 
    return centre;
}

double distance_between_two_points(double p1x, double p1y, double p2x, double p2y){
    double square_of_x = pow((p1x - p2x), 2);
    double square_of_y = pow((p1y - p2y), 2);
    double dist = sqrt(square_of_x + square_of_y);
    return dist;
}


// Using Cramer's rule:
void line_aux(double point1[], double point2[], double *L){
    L[0] = (point1[1] - point2[1]);
    L[1] = (point2[0] - point1[0]);
    L[2] = -((point1[0]*point2[1] - point2[0]*point1[1]));
}

int intersection_aux(double L1[], double L2[], double *P){
    double D  = L1[0] * L2[1] - L1[1] * L2[0];
    double Dx = L1[2] * L2[1] - L1[1] * L2[2];
    double Dy = L1[0] * L2[2] - L1[2] * L2[0];
    double x, y;
    if(D != 0){
        P[0] = Dx / D;
        P[1] = Dy / D;
        return 1;
    }
    else return 0;
}

int get_lines_intersection(double P1[], double P2[], double P3[], double P4[], double *solution){
    double *L1 = malloc(sizeof(double) * 3);
    double *L2 = malloc(sizeof(double) * 3);

    line_aux(P1, P2, L1);
    line_aux(P3, P4, L2);

    if(intersection_aux(L1, L2, solution)){
        free(L1);
        free(L2);
        return 1;
    }
    free(L1);
    free(L2);
    return 0;
}

void linear_expansion(double p0x, double p0y, double p1x, double p1y, double length, double *solution){
    double distance = distance_between_two_points(p0x, p0y, p1x, p1y);

    solution[0] = p1x + (p1x - p0x) / distance * length;
    solution[1] =  p1y + (p1y - p0y) / distance * length;
}
