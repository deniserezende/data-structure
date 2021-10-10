// 
//  geometry_operations.c
//  
//
//  Created by Denise F. de Rezende on 15/06/21.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "geometry_operations.h"

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

// Note that: this function returns 1 if the point is inside the circle or in it's border.
int point_in_circle(type_circle circle, double px, double py){
    double circlex = get_circle_x(circle);
    double circley = get_circle_y(circle);
    double circler = get_circle_radius(circle);
    // If the distance between the center of the circle and the point is less or equal to radius
    // the point is in the circle!
    double dist = distance_between_two_points(circlex, circley, px, py);
    if(dist <= circler) return 1;
    return 0;
}

// Note that: if the circles are exactly the same the function considers one inside the other.
int circle_in_circle(type_circle reference_circle, type_circle second_circle){
    double rcirclex = get_circle_x(reference_circle);
    double rcircley = get_circle_y(reference_circle);
    double rcircler = get_circle_radius(reference_circle);
    double scirclex = get_circle_x(second_circle);
    double scircley = get_circle_y(second_circle);
    double scircler = get_circle_radius(second_circle);
    double dist_of_centers = distance_between_two_points(rcirclex, rcircley, scirclex, scircley);
    if((dist_of_centers + scircler) <= rcircler){
        return 1;
    }
    return 0;
}

int circle_center_in_circle(type_circle reference_circle, type_circle second_circle){
    double rcirclex = get_circle_x(reference_circle);
    double rcircley = get_circle_y(reference_circle);
    double rcircler = get_circle_radius(reference_circle);
    double scirclex = get_circle_x(second_circle);
    double scircley = get_circle_y(second_circle);
    double dist_of_centers = distance_between_two_points(rcirclex, rcircley, scirclex, scircley);
    if((dist_of_centers) <= rcircler){
        return 1;
    }
    return 0;
}

// Note that: the circle can touch the rectangle's border.
int circle_in_rect(type_rect rect, type_circle circle){ 
    double circlex = get_circle_x(circle);
    double circley = get_circle_y(circle);
    double circler = get_circle_radius(circle);
    double rectx = get_rect_x(rect);
    double rectwidth = get_rect_width(rect);
    double recty = get_rect_y(rect);
    double rectheight = get_rect_height(rect);
    if((rectx <= circlex-circler) && (rectx+rectwidth >= circlex+circler) && 
        (recty <= circley+circler) && (recty+rectheight >= circley-circler)){
        return 1;
    }
    return 0;
}

int circle_center_in_rect(type_rect rect, type_circle circle){ 
    double circlex = get_circle_x(circle);
    double circley = get_circle_y(circle);
    double circler = get_circle_radius(circle);
    double rectx = get_rect_x(rect);
    double rectwidth = get_rect_width(rect);
    double recty = get_rect_y(rect);
    double rectheight = get_rect_height(rect);
    if((rectx <= circlex) && (rectx+rectwidth >= circlex) && 
        (recty <= circley) && (recty+rectheight >= circley)){
        return 1;
    }
    return 0;
}

// Function that checks if a point is in a segment.
int point_in_segment(type_segment segment, double px, double py){
    double x1 = get_segment_first_x(segment);
    double y1 = get_segment_first_y(segment);
    double x2 = get_segment_second_x(segment);
    double y2 = get_segment_second_y(segment);
    return (distance_between_two_points(x1,y1,px,py)+ distance_between_two_points(x2,y2,px,py) == distance_between_two_points(x1,y1,x2,y2));
}

int intersection_of_segments(type_segment segment1, type_segment segment2){
    double Ax = get_segment_first_x(segment1); // Ax
    double Ay = get_segment_first_y(segment1); // Ay
    double Bx = get_segment_second_x(segment1); // Bx
    double By = get_segment_second_y(segment1); // By
    double Cx = get_segment_first_x(segment2); // Cx
    double Cy = get_segment_first_y(segment2); // Cy
    double Dx = get_segment_second_x(segment2); // Dx
    double Dy = get_segment_second_y(segment2); // Dy

    double diff1x = Bx - Ax;
    double diff2x = Dx - Cx;
    double diff1y = By - Ay;
    double diff2y = Dy - Cy;
    double p0 = diff2y*(Dx-Ax) - diff2x*(Dy-Ay);
    double p1 = diff2y*(Dx-Bx) - diff2x*(Dy-By);
    double p2 = diff1y*(Bx-Cx) - diff1x*(By-Cy);
    double p3 = diff1y*(Bx-Dx) - diff1x*(By-Dy);
    return (p0*p1<=0) & (p2*p3<=0);
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

int get_segment_intersection(type_segment segment1, type_segment segment2, double *solution){
    double P1[2], P2[2], P3[2], P4[2];
    P1[0] = get_segment_first_x(segment1);
    P1[1] = get_segment_first_y(segment1);
    P2[0] = get_segment_second_x(segment1);
    P2[1] = get_segment_second_y(segment1);
    P3[0] = get_segment_first_x(segment2);
    P3[1] = get_segment_first_y(segment2);
    P4[0] = get_segment_second_x(segment2);
    P4[1] = get_segment_second_y(segment2);

    return(get_lines_intersection(P1, P2, P3, P4, solution));

}

void linear_expansion(double p0x, double p0y, double p1x, double p1y, double length, double *solution){
    double distance = distance_between_two_points(p0x, p0y, p1x, p1y);

    solution[0] = p1x + (p1x - p0x) / distance * length;
    solution[1] =  p1y + (p1y - p0y) / distance * length;
}
