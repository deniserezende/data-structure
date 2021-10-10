// 
//  im_t30_nve.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef im_t30_nve_h
#define im_t30_nve_h
#include "kd_tree.h"
#include "list.h"
#include "rectangle.h"
#include "circle.h"
#include "segment.h"
#include "person.h"
#include "meteor.h"
#include "geometry_operations.h"
#include "TXT.h"
#include "output_txt.h"

// Function that calculates the exposure to radiation (which is cumulative) of each person in the given kdtree of circles
// and reports, in the given txtfile, the id of each person that died or who's death is imminent.
void im(type_meteor meteor, type_kdtree circles, type_kdtree hsegments, type_kdtree vsegments, type_txt txtfile);


// Function that calculates the level of exposure to radiation in a given point
// and reports, in the given txtfile, the level of radiation calculated.
// This function considers all previous meteors.
double nve(double point_x, double point_y, type_list meteors, type_kdtree hsegments, type_kdtree vsegments, type_txt txtfile);


// Function that informs the passing of 30 minutes, which means each person who's death was imminent died
// and reports, in the given txtfile, the id of each person that died.
void t30(type_kdtree circles, type_txt txtfile);


// Function that returns the color corresponding to the radiation level.
// Note that: this function returns a malloc char*, so to avoid memory leak:
// after using the data, free the variable used to receive the result of this function.
char* get_radiation_exposure_color(double radiation);

#endif /* im_t30_nve_h */


