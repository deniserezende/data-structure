#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "SVG.h"

typedef struct svg_structure {
	FILE *fsvg;
	char *stroke, *fill;
	double stroke_width;
}STRUCTSVG;

// These global variables will be used for the functions with cartesian system
double delta_x = 0, delta_y = 0; //origin point???
double x_max = 0, y_max = 6000; //default?
double axis_width, axis_height;


// Pre-conditions: None
/* Post-conditions: Creates a new file in the directory specified with the filename specified
(How to specify the directory and filname: path/filename.svg = fullpath) 
if a file with that name already exists in that directory, that file is overwritten
if the file can't be created because the path is incomplete or incorrect, returns NULL. */ 
type_svg start_new_svg_file(char *fullpath){
	FILE *f = fopen(fullpath,"w"); //open to write
	if (f == NULL){
		return NULL;
	}

	STRUCTSVG *svg_cell = malloc(sizeof(STRUCTSVG));
	svg_cell->fsvg = f; 
	svg_cell->stroke = NULL;
	svg_cell->fill = NULL;
	svg_cell->stroke_width = 0.0;

	fprintf(svg_cell->fsvg,"<svg xmlns=\"http://www.w3.org/2000/svg\"\n\txmlns:xlink=\"http://www.w3.org/1999/xlink\" >\n");
	return svg_cell;
}

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A rectangle has been inserted.
void insert_rectangle_in_svg(type_svg file, double x, double y, double width, double height, char *fill, char *stroke, double stroke_width){
	STRUCTSVG *fsf = file; 
	fprintf(fsf->fsvg,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\"  fill=\"%s\"  stroke-width=\"%f\"/>\n", x, y, width, height, stroke, fill, stroke_width);
}

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A style has been defined as standard (fill, stoke, stroke_width).
void define_standard_style(type_svg file, char *fill, char *stroke, double stroke_width){
	STRUCTSVG *fsf = file;

	fsf->fill = malloc((strlen(fill)+1) * sizeof(char));
	sprintf(fsf->fill, "%s", fill);

	fsf->stroke = malloc( (strlen(stroke)+1) * sizeof(char));
	sprintf(fsf->stroke, "%s", stroke);	

	fsf->stroke_width = stroke_width;
}

// Pre-condition: The svg file has to have been 'started' and a standard style has to have been defined.
// Post-condition: A standard rectangle has been inserted.
void insert_standard_rectangle(type_svg file, double x, double y, double width, double height){
	STRUCTSVG *fsf = file;
	insert_rectangle_in_svg(file, x, y, width, height, fsf->fill, fsf->stroke, fsf->stroke_width);
}

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: A rectangle has been inserted.
void insert_rectangle_based_in_opposite_corners(type_svg file, double x1, double y1, double x2, double y2, char *fill, char *stroke, double stroke_width){
	STRUCTSVG *fsf = file; 
	double x, y, width, height;

	x = x1 < x2? x1: x2;
	y = y1 < y2? y1: y2;
	width = fabs(x2-x1);
	height = fabs(y2-y1);

	fprintf(fsf->fsvg,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\"  fill=\"%s\"  stroke-width=\"%f\"/>\n", x, y, width, height, stroke, fill, stroke_width);
}

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A dashy rectangle has been inserted.
void insert_dasharray_rect_based_in_opposite_corners_in_svg(type_svg file, double x1, double y1, double x2, double y2, char *fill, char *stroke, double stroke_width, double stroke_dash){
	STRUCTSVG *fsf = file; 
	double x, y, width, height;

	x = x1 < x2? x1: x2;
	y = y1 < y2? y1: y2;
	width = fabs(x2-x1);
	height = fabs(y2-y1);
	
	
	fprintf(fsf->fsvg,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\"  fill=\"%s\"  stroke-width=\"%f\" stroke-dasharray=\"%f\" />\n", x, y, width, height, stroke, fill, stroke_width, stroke_dash);
}

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A circle has been inserted.
void insert_circle_in_svg(type_svg file, double x, double y, double radius, char *fill, char *stroke, double stroke_width){
	STRUCTSVG *fsf = file; 
	fprintf(fsf->fsvg,"\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\"  fill=\"%s\"  stroke-width=\"%f\"/>\n", x, y, radius, stroke, fill, stroke_width);
}

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A line has been inserted.
void insert_line_in_svg(type_svg file, double xstart, double ystart, double xend, double yend, char *stroke, double stroke_width){
	STRUCTSVG *fsf = file; 
	fprintf(fsf->fsvg,"\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%f\"/>\n", xstart, ystart, xend, yend, stroke, stroke_width);
}

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A text has been inserted.
void insert_text_in_svg(type_svg file, double x, double y, char *fill, char *text, double font_size){
	STRUCTSVG *fsf = file; 
	fprintf(fsf->fsvg,"\t<text x=\"%f\" y=\"%f\" fill=\"%s\" font-size=\"%f\"> %s </text>\n", x, y, fill, font_size, text);
}

/* --------------------------------------------------------------------------------------------------
Note that: variables sent to the functions with the cartesian system, has to be in the svg parameters, 
and the functions will convert them to your cartesian system.
--------------------------------------------------------------------------------------------------- */

// Pre-conditon: The svg file has to have been 'started'.
// Post-condition: A x and y maximum value has been set
void set_max_size_for_cartesian_coordinates_in_svg(double max_x, double max_y){
	x_max = max_x;
	y_max = max_y;
}

// Pre-conditon: The svg file has to have been 'started' and  a x and y maximum value has to have been set.
// Post-condition: The cartesian axis has been inserted.
void insert_cartesian_axis_in_svg(type_svg file, double origin_x, double origin_y, double width, double height){
	STRUCTSVG *fsf = file; 
	delta_x = origin_x;
	delta_y = origin_y;
	axis_width = width;
	axis_height = height;

	insert_line_in_svg(file, delta_x, delta_y, (delta_x+width), delta_y, "black", 1);
	insert_line_in_svg(file, delta_x, delta_y, delta_x, (delta_y-height), "black", 1);
}

// Pre-conditon: The svg file has to have been 'started' and  a x and y maximum value has to have been set.
// Post-condition: The reference lines have been inserted.
void insert_reference_line_in_cartesian_system_in_svg(type_svg file, int amountx, int amounty){
	int incrementx, incrementy, x, y;
	incrementx = axis_width / amountx;
	incrementy = axis_height / amounty;


	for(x = delta_x + incrementx; x <= delta_x + axis_width; x = x + incrementx){
		insert_line_in_svg(file, x, delta_y+2, x, delta_y-2, "black", 1);
	}
	for(y = delta_y - incrementy; y >= delta_y - axis_height; y = y - incrementy){
		insert_line_in_svg(file, delta_x-2, y, delta_x+2, y, "black", 1);
	}
}

/*  Note that: It's recommended that the amountx and amounty sent to the function 
'insert_reference_line_in_cartesian_system_in_svg' is the same to be sent to the function below  */
// Pre-conditon: The reference lines have to have been inserted.
// Post-condition: The reference numbers have been inserted.
void insert_numbers_in_reference_lines_in_svg(type_svg file, int amountx, int amounty){
	double incrementx, incrementy;
	double n, x, y;
	char *tempstr = malloc(sizeof(char) * 50);
	incrementx = x_max / amountx;
	incrementy = y_max / amounty;
	
	sprintf(tempstr,"%d", (int)0);
	insert_text_in_svg(file, delta_x, delta_y+20, "black", tempstr, 10);
	strcpy(tempstr, "\0");

	n = incrementx;
	for(x = delta_x + (axis_width / amountx); x <= delta_x + axis_width; x = x + (axis_width / amountx)){
		sprintf(tempstr,"%d", (int)n);
		insert_text_in_svg(file, x, delta_y+20, "black", tempstr, 10);
		strcpy(tempstr, "\0");
		n = n + incrementx;
	}
	n = incrementy;
	for(y = delta_y - (axis_height / amounty); y >= delta_y - axis_height; y = y - (axis_height / amounty)){
		sprintf(tempstr,"%d", (int)n);
		insert_text_in_svg(file, delta_x-40, y, "black", tempstr, 10);
		strcpy(tempstr, "\0");
		n = n + incrementy;
	}

	free(tempstr);
}

// Pre-conditon: The cartesian axis has to have been inserted.
// Post-condition: The point has been inserted.
void insert_point_in_cartesian_system_in_svg(type_svg file, double x, double y){
	double real_x, real_y;

	real_x = (x / x_max * axis_width) + delta_x;
	real_y = -(y/ y_max * axis_height) + delta_y;

	insert_circle_in_svg(file, real_x, real_y, 2.0, "blue", "blue", 1.0);
}

// Pre-conditon: The cartesian axis has to have been inserted.
// Post-condition: The text has been inserted.
void insert_text_in_cartesian_system_in_svg(type_svg file, double x, double y, char *fill, char *text, double font_size){
	double real_x, real_y;

	real_x = (x / x_max * axis_width) + delta_x;
	real_y = -(y/ y_max * axis_height) + delta_y;

	insert_text_in_svg(file, real_x, real_y, fill, text, font_size);
}

// Pre-conditon: The cartesian axis has to have been inserted.
// Post-condition: The line has been inserted.
void insert_line_in_cartesian_system_in_svg(type_svg file, double xstart, double ystart, double xend, double yend, char *stroke, double stroke_width){
	int real_x1, real_x2, real_y1, real_y2;

	real_x1 = (xstart / x_max * axis_width) + delta_x;
	real_y1 = -(ystart/ y_max * axis_height) + delta_y;

	real_x2 = (xend / x_max * axis_width) + delta_x;
	real_y2 = -(yend/ y_max * axis_height) + delta_y;

	insert_line_in_svg(file, real_x1, real_y1, real_x2, real_y2, "black", 1);
}

// Pre-condition: The svg file has to have been 'started'.
// Post-condition: The svg file is now closed. 
// The effect of any other operation called in the closed file is unpredictable. 
void end_svg_file(type_svg file){
	STRUCTSVG *fsf = file;
  	fprintf(fsf->fsvg,"\n</svg>\n");
	fclose(fsf->fsvg);

	if(fsf->fill != NULL) free(fsf->fill);
	if(fsf->stroke != NULL) free(fsf->stroke);
	free(fsf);
}


