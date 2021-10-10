// 
//  dpi_dr.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef dpi_dr_h
#define dpi_dr_h
#include "kd_tree.h"
#include "binary_search_tree.h"
#include "rectangle.h"
#include "building.h"
#include "geometry_operations.h"
#include "TXT.h"
#include "output_txt.h"

// Function that deactivates all rectangles in which the point (px,py) is internal
// and reports the id of the rectangles deactivated in a given txtfile.
void dpi(type_kdtree rects, float px, float py, type_txt txtfile);


// Function that deactivates all rectangles which are in a given rectangle (reference_rect)
// and reports the id of the rectangles deactivated in a given txtfile.
void dr(type_kdtree rects, type_rect reference_rect, type_txt txtfile);


#endif /* dpi_dr_h */