// 
//  rectangle.h
//  
//
//  Created by Denise F. de Rezende on 25/05/21.
//

#ifndef rectangle_h
#define rectangle_h

typedef void* type_rect;
typedef void* type_rectdata;

// Creates new rectangles with the parameters specified
type_rect new_rectangle(char id[], double x, double y, double w, double h, char stroke[], char fill[]);

type_rect copy_rectangle(type_rect rectangle);
 
// Destrois the rectangle, so that it does not exist anymore
void destroi_rectangle(type_rect rectangle);

// Function to insert extra data in a rectangle
void insert_data_in_rect(type_rect rectangle, type_rectdata data);

// Function returns 0 if equal, 1 if the first one is bigger and -1 if the first one is smaller
// Note that: axis = 0 -> x; 	and 	axis = 1 -> y;
long compare_rectangles_by_reference_point(type_rect rectangle1, type_rect rectangle2, int axis);
long compare_rectangle_reference_point_with_point(type_rect rectangle, double pointx, double pointy, int axis);
long compare_rectangles_by_id(type_rect rectangle1, type_rect rectangle2);

// Function returns 0 if equal, 1 if the first one is bigger and -1 if the first one is smaller
long compare_rectangles_by_x_coordinate(type_rect rectangle1, type_rect rectangle2);

// Functions to get information from the rectangle:
int check_if_id_match_rects(type_rect rectangle, char *name);
int check_if_rects_ids_match(type_rect rectangle1, type_rect rectangle2);
char* get_rect_id(type_rect rect);
double get_rect_x(type_rect rect);
double get_rect_y(type_rect rect);
double get_rect_width(type_rect rect);
double get_rect_height(type_rect rect);
char* get_rect_stroke_color(type_rect rect);
char* get_rect_fill_color(type_rect rect);
type_rectdata get_rect_data(type_rect rect);

// Functions to change information from the rectangle:
void change_rect_x(type_rect rect, double newx);
void change_rect_y(type_rect rect, double newy);
void change_rect_width(type_rect rect, double new_width);
void change_rect_height(type_rect rect, double new_height);
void change_rect_fill_color(type_rect rect, char *new_fill);
void change_rect_stroke_color(type_rect rect, char *new_stroke);
void change_rect_data(type_rect rect, type_rectdata new_data);


// Functions to add information
void add_rectangles_stroke_width(type_rect rectangle, double stroke_width);

#endif /* rectangle_h */



