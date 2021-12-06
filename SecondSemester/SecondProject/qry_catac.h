// 
//  qry_catac.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_dmpt_catac_h
#define qry_dmpt_catac_h
#include "hash_table.h"
#include "rectangle.h" 
#include "block.h"
#include "_auxiliary_functions.h"
#include "SVG.h"
#include "TXT.h"
#include "graph.h"
#include "vertex.h"
#include "_geometry_operations.h"
#include "edge.h"

// Remover as quadras contidas na região delimitada pelo retângulo x,y,w,h. Arestas incidentes em vértices 
// dentro do retângulo especificado devem ser removidas.
// TXT: imprimir identificadores e dados associados a tudo o que foi removido.
// SVG: elementos removidos não devem aparecer. Desenhar sob o mapa o referido retângulo com
// cor de preenchimento #AB37C8, cor de borda #AA0044 e com 50% de transparência se pelo menos um dos vértices 
// da aresta estiver dentro da área do catac, vai remover essa aresta, não vai remover o vértice e 
// no svg a gente pode printar o vértice boiando.
type_mMlavltree catac(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_hashtable, type_graph via_graph, double x, double y, double w, double h);

#endif