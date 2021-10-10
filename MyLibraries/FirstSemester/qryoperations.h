//
//  qryoperations.h -> interprets the qryfile of the second project of Data Structure
//  
//
//  Created by Denise F. de Rezende on 25/05/21.
//
#ifndef qryoperations_h
#define qryoperations_h
#include "kd_tree.h"
#include "list.h"
#include "rectangle.h"
#include "circle.h"
#include "segment.h"
#include "building.h"
#include "person.h"
#include "meteor.h"
#include "geometry_operations.h"
#include "dpi_dr.h"
#include "fg.h"
#include "im_t30_nve.h"
#include "TXT.h"
#include "SVG.h"
#include "output_svg.h"


// Function that interprets the qry file, calls functions and produces outputs: one svg file and one txt file
// both output files have to have been started and sent to this function.
void read_qry_and_report_called_functions(char *qryfilename, type_txt txtfile, type_svg svgfile, type_kdtree rects, type_kdtree circles);

#endif /* qryoperations_h */
