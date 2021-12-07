// 
//  qry_o_.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_o_h
#define qry_o_h
#include "SVG.h"
#include "TXT.h"
#include "property.h"
#include "_auxiliary_functions.h"
#include "hash_table.h"
#include "_geometry_operations.h"

// Armazena no registrador r a posição geográfica do endereço cep/face/num
// SVG: linha vertical com identificação do registrador.
type_property o_(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_hash, char cep[], char cardinal_direction, int house_number, double viewbox[]);

#endif