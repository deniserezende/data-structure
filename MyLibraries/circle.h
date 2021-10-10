// 
//  circle.h
//  
//
//  Created by Denise F. de Rezende on 09/06/21.
//

#ifndef circle_h
#define circle_h

typedef void* type_circle;
typedef void* type_circdata;

// Creates new circle with the parameters specified
type_circle new_circle(char id[], double x, double y, double r, char stroke[], char fill[]);

// Returns a copy of an existing circle
type_circle copy_circle(type_circle circle);

// Destrois the circle, so that it does not exist anymore.
void destroi_circle(type_circle circle);

// Function to insert extra data in a circle
void insert_data_in_circle(type_circle circle, type_circdata data);

// Functions bellow return:
// 0 when equal
// 1 when the first one is bigger 
// -1 when the first one is smaller
// Note that: axis = 0 -> x; 	and 	axis = 1 -> y;
long compare_circles_centers(type_circle circle1, type_circle circle2, int axis);
long compare_circle_center_with_point(type_circle circle, double pointx, double pointy, int axis);
long compare_circles_by_id(type_circle circle1, type_circle circle2);

// Functions to get information from the circle:
char* get_circle_id(type_circle circle);
double get_circle_x(type_circle circle);
double get_circle_y(type_circle circle);
double get_circle_radius(type_circle circle);
char* get_circle_stroke_color(type_circle circle);
char* get_circle_fill_color(type_circle circle);
type_circdata get_circle_data(type_circle circle);

// Functions to change information from the circle:
void change_circle_x(type_circle circle, double newx);
void change_circle_y(type_circle circle, double newy);
void change_circle_radius(type_circle circle, double new_radius);
void change_circle_fill_color(type_circle circle, char new_fill[]);
void change_circle_stroke_color(type_circle circle, char new_stroke[]);
void change_circle_data(type_circle circle, type_circdata new_data);

#endif /* circle_h */
