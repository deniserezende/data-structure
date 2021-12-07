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

// Calcule a árvore geradora mínima do subgrafo com os vértices que estão dentro da região
// especificada pela retângulo x,y,w,h. A velocidade dos trechos relativos às arestas da árvore
// geradora mínima deve ser reduzida, a cada nível da árvore, de acordo com o fator f (0.0 < f <
// 1.0), até, no mínimo, 0.01 (ou seja, 1%). Por exemplo, se f = 0.05, a velocidade deve ser
// reduzida de 5% da velocidade original nas arestas que ligam a raiz da árvore aos seus
// filhos; de 10% nas arestas que ligam os filhos aos netos; de 15%, nas que ligam os netos aos
// bisnetos e assim sucessivamente.
// TXT: reportar arestas da AGM, incluindo seus atributos (busca em largura)
// SVG: pintar as arestas da AGM com um traço bastante largo e de uma cor clara. Delimitar a
// região x,y,w,h com um retângulo de bordas grossas e tracejadas. ATENÇÃO: Indicar a raiz da AGM
void rv(type_svg SVGFILE,type_txt TXTFILE, type_graph via_graph, double x, double y, double w, double h, double f);

#endif