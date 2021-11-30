//
//  pm_operations.h -> interprets the geofile of the first project of Data Structure II
//  
//
//  Created by Denise F. de Rezende on 12/09/21.
//



#ifndef qry_operations_h
#define qry_operations_h

#include "SVG.h"
#include "TXT.h"
#include "qry_catac.h"
#include "qry_p_.h"
#include "qry_o_.h"
#include "qry_cx.h"
#include "qry_rv.h"

#include "output_svg.h"
#include "path.h"
#include "graph.h"
#include "property.h"


type_mMlavltree get_qry_input_and_generate_output(char *qryfilename, char *output_path, char *geo_filename, type_txt txtfile, type_svg svgfile, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_graph via_graph, double viewbox[4]);

#endif /* qry_operations_h */
