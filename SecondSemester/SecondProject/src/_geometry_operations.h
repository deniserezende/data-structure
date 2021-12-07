// 
//  geometry_operations.h
//  
//
//  Created by Denise F. de Rezende on 15/06/21.
//

#ifndef geometry_operations_h
#define geometry_operations_h

#include "rectangle.h"

// Function that verifies whether a point is inside the rect or in it's border, if so returns 1.
int point_in_rect(type_rect rect, double px, double py);

// Function that verifies whether a rectangle is inside another one
// Note that: if the rectangles are exactly the same the function considers one inside the other.
int rect_in_rect(type_rect reference_rect, type_rect second_rect);

// Function that calculates the centre of mass of a rectangle 
// Note that: the reference point of the rectangle has to be the lowest x and y.
// Note that: this function returns a malloc double*, so to avoid memory leak:
// after using the data, free the variable used to receive the result of this function.
double* centre_of_mass_rect(type_rect rect);

// Function that calculates the distance between two points.
double distance_between_two_points(double p1x, double p1y, double p2x, double p2y);

// Function that get's the intersection of two lines
// Note that: this function returns 1, if intersection found, else returns 0.
// and the solution is given in the last parameter, if it exists.
int get_lines_intersection(double P1[], double P2[], double P3[], double P4[], double *solution);

// Function that calculates given the paramenters, the linear expansion.
void linear_expansion(double p0x, double p0y, double p1x, double p1y, double length, double *solution);

#endif /* geometry_operations_h */

