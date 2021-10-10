//
//  geooperations.h -> interprets the geofile of the second project of Data Structure
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#ifndef geooperations_h
#define geooperations_h
#include "kd_tree.h"
#include "rectangle.h"
#include "circle.h"
#include "building.h"
#include "person.h"

// Reads and interprets the geofile, adding circles and rectangles to the respective kdtree sent.
void read_geo_and_saves_info(char *filename, type_kdtree *circle_kdtree, type_kdtree *rect_kdtree);

#endif /* geooperations_h */
