// 
//  segment.h
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#ifndef segment_h
#define segment_h

typedef void* type_segment;
typedef void* type_segdata;

// Creates new segment with the parameters specified
type_segment new_segment(char id[], double x, double y, double x2, double y2, char stroke[]);

// Creates new basic segment with the parameters specified
type_segment new_segment_basic(double x, double y, double x2, double y2);

// Copys basic segment.
type_segment copy_segment_basic(type_segment segment);


// Destrois the segment, so that it does not exist anymore
void destroi_segment(type_segment segment);

// Function returns 0 if equal, 1 if the first one is bigger and -1 if the first one is smaller
// Note that: axis = 0 -> x; 	and 	axis = 1 -> y;
long compare_segments_by_first_point(type_segment segment1, type_segment segment2, int axis);
long compare_segment_first_point_with_point(type_segment segment, double pointx, double pointy, int axis);


// Function to insert extra data in a segment
void insert_data_in_segment(type_segment segment, type_segdata data);

// Functions to get information from the segment:
char* get_segment_id(type_segment segment);
double get_segment_first_x(type_segment segment);
double get_segment_first_y(type_segment segment);
double get_segment_second_x(type_segment segment);
double get_segment_second_y(type_segment segment);
char* get_segment_stroke_color(type_segment segment);
type_segdata get_segment_data(type_segment segment);

// Functions to change information from the segment:
void change_segment_first_x(type_segment segment, double newx);
void change_segment_first_y(type_segment segment, double newy);
void change_segment_second_x(type_segment segment, double newx2);
void change_segment_second_y(type_segment segment, double newy2);
void change_segment_stroke_color(type_segment segment, char new_stroke[]);
void change_segment_data(type_segment segment, type_segdata new_data);


#endif /* segment_h */




