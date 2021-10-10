// 
//  fg.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef fg_h
#define fg_h
#include "kd_tree.h"
#include "binary_search_tree.h"
#include "rectangle.h"
#include "circle.h"
#include "building.h"
#include "person.h"
#include "geometry_operations.h"
#include "TXT.h"
#include "output_txt.h"

// Function that moves people inside a given circle area to the closest building
// and reports the id of each building followed by the id of each person moved inside in a given txtfile.
void fg(type_circle reference_circle, type_kdtree circles, type_kdtree rects, type_txt txtfile);


#endif /* fg_h */