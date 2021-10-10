//
//  SVG.h
//  
//
//  Created by Denise F. de Rezende on 13/03/21.
//

#ifndef SVG_h
#define SVG_h

/* This module provides functions for the creation of a svg file.
	To create a svg file you need to: 
	1- start the creation process with the "start_new_svg_file" function.
	2- if you want elements in it, call the function that inserts the element you want.
	3- end the creation process with the "end_svg_file" function.

	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

typedef void *type_svg;

// Pre-conditions: None
/* Post-conditions: Creates a new file in the directory specified with the filename specified
(How to specify the directory and filname: path/filename.svg = fullpath) 
if a file with that name already exists in that directory, that file is overwritten
if the file can't be created because the path is incomplete or incorrect, returns NULL. */ 
type_svg start_new_svg_file(char *fullpath);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A comment has been inserted.
void insert_comment_in_svg(type_svg file, char *string);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A rectangle has been inserted.
void insert_rectangle_in_svg(type_svg file, double x, double y, double width, double height, char *fill, char *stroke, double stroke_width);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A rectangle with rounded corners has been inserted.
void insert_rectangle_with_rounded_corners_in_svg(type_svg file, double x, double y, double width, double height,  double rx, double ry, char *fill, char *stroke, double stroke_width);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A style has been defined as standard (fill, stoke, stroke_width).
void define_standard_style(type_svg file, char *fill, char *stroke, double stroke_width);

// Pre-condition: The svg file has to have been 'started' and a standard style has to have been defined.
// Post-condition: A standard rectangle has been inserted.
void insert_standard_rectangle(type_svg file, double x, double y, double width, double height);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A rectangle has been inserted.
void insert_rectangle_based_in_opposite_corners(type_svg file, double x1, double y1, double x2, double y2, char *fill, char *stroke, double stroke_width);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A rectangle has been inserted.
void insert_rectangle_with_different_opacity_in_svg(type_svg file, double x, double y, double width, double height, char *fill, char *stroke, double fillopacity, double stroke_width);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A dashy rectangle has been inserted.
void insert_dasharray_rect_based_in_opposite_corners_in_svg(type_svg file, double x1, double y1, double x2, double y2, char *fill, char *stroke, double stroke_width, double stroke_dash);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A dashy rectangle has been inserted.
void insert_dasharray_rect_in_svg(type_svg file, double x, double y, double width, double height, char *fill, char *stroke, double stroke_width, double stroke_dash);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A circle has been inserted.
void insert_circle_in_svg(type_svg file, double x, double y, double radius, char *fill, char *stroke, double stroke_width);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A ellipse has been inserted.
void insert_ellipse_in_svg(type_svg file, double x, double y, double rx, double ry, char *fill, char *stroke, double stroke_width);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A circle has been inserted with the opacity specified.
// Note that: fillopacity varies between 0 and 1.
void insert_circle_with_different_opacity_in_svg(type_svg file, double x, double y, double radius, char *fill, char *stroke, double fillopacity, double stroke_width);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: An animated circle has been inserted.
void insert_animated_circle_in_svg(type_svg file, double x, double y, double x2, double y2, double radius, char *fill, char *stroke, double stroke_width, char* pathfill, int dasharray, char *dashstroke, double dashwidth, int duration, char* repeatcount);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A line has been inserted.
void insert_line_in_svg(type_svg file, double xstart, double ystart, double xend, double yend, char *stroke, double stroke_width);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A dashy line has been inserted.
void insert_dashy_line_in_svg(type_svg file, double xstart, double ystart, double xend, double yend, char *stroke, double stroke_width, double stroke_dash);

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A text has been inserted.
void insert_text_in_svg(type_svg file, double x, double y, char *fill, char *text, double font_size);


/* --------------------------------------------------------------------------------------------------
Note that: variables sent to the functions with the cartesian system, has to be in the svg parameters, 
and the functions will convert them to your cartesian system.
--------------------------------------------------------------------------------------------------- */

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A x and y maximum value has been set
void set_max_size_for_cartesian_coordinates_in_svg(double max_x, double max_y);

// Pre-conditon: The svg file has to have been 'started' and  a x and y maximum value has to have been set.
// Post-condition: The cartesian axis has been inserted.
void insert_cartesian_axis_in_svg(type_svg file, double origin_x, double origin_y, double width, double height);

// Pre-conditon: The svg file has to have been 'started' and  a x and y maximum value has to have been set.
// Post-condition: The reference lines have been inserted.
void insert_reference_line_in_cartesian_system_in_svg(type_svg file, int amountx, int amounty);

/*  Note that: It's recommended that the amountx and amounty sent to the function 
'insert_reference_line_in_cartesian_system_in_svg' is the same to be sent to the function below  */
// Pre-conditon: The reference lines have to have been inserted.
// Post-condition: The reference numbers have been inserted.
void insert_numbers_in_reference_lines_in_svg(type_svg file, int amountx, int amounty);

// Pre-conditon: The cartesian axis has to have been inserted.
// Post-condition: The point has been inserted.
void insert_point_in_cartesian_system_in_svg(type_svg file, double x, double y);

// Pre-conditon: The cartesian axis has to have been inserted.
// Post-condition: The text has been inserted.
void insert_text_in_cartesian_system_in_svg(type_svg file, double x, double y, char *fill, char *text, double font_size);

// Pre-conditon: The cartesian axis has to have been inserted.
// Post-condition: The line has been inserted.
void insert_line_in_cartesian_system_in_svg(type_svg file, double xstart, double ystart, double xend, double yend, char *stroke, double stroke_width);

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: The svg file is now closed. 
// The effect of any other operation called in the closed file is unpredictable. 
void end_svg_file(type_svg file);

#endif /* SVG_h */ 


 
