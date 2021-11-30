#ifndef qry_rv_h
#define qry_rv_h

#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include "rectangle.h"
#include "_geometry_operations.h"
#include "kruskals_algorithm.h"
#include "_auxiliary_functions.h"
#include "SVG.h"

void rv(type_svg SVGFILE,type_txt TXTFILE, type_graph via_graph, double x, double y, double w, double h, double f);


#endif