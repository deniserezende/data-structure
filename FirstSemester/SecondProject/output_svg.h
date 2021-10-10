//
//  output_svg.h -> Used for the second project of Data Structure
//  
//
//  Created by Denise F. de Rezende on 09/06/21.
//

#ifndef output_svg_h
#define output_svg_h

#include "SVG.h"
#include "kd_tree.h"
#include "list.h"
#include "rectangle.h"
#include "circle.h"
#include "person.h"
#include "building.h"
#include "meteor.h"

// Insert rectangles in svg
void insert_rects_in_svg(type_svg svgfile, type_kdtree rects);
void insert_active_rects_in_svg(type_svg svgfile, type_kdtree rects);
void insert_one_rect_in_svg(type_svg svgfile, type_rect rect);

// Insert circles in svg
void insert_circles_in_svg(type_svg svgfile, type_kdtree circles);
void insert_circles_considering_status_in_svg(type_svg svgfile, type_kdtree circles);

// Insert meteor in svg
void insert_meteors_in_svg(type_svg svgfile, type_list meteors);

// Function that reports how many people are inside each building
// this function is only used after calling the fg function.
void fg_report_in_svg_circles_inside_rects(type_svg svgfile, type_kdtree rects);

// print rects and circles in terminal.
void print_rects_and_circles_DEBUG(type_kdtree rects, type_kdtree circles);


#endif /* output_svg_h */