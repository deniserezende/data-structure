#include "qry_catac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

type_svg QDC_SVGFILE;
type_txt QDC_TXTFILE;

type_hashtable QDC_blocks_table;
type_mMlavltree QDC_blocks_avl;
double QDC_x1, QDC_y1, QDC_h, QDC_w;
char QDC_ID[40];
type_list QDC_blocks_to_delete;
type_list QDC_list;


void _catac_svg(type_mMlavlitems block_rect){
    insert_rectangle_with_different_opacity_in_svg(QDC_SVGFILE, get_rect_x(block_rect), get_rect_y(block_rect), get_rect_width(block_rect), get_rect_height(block_rect), "#AB37C8", "#AA0044", 0.5, 2);
}

void action_catac_blocks(type_mMlavlitems block_rect){
    type_block block = get_rect_data(block_rect);
    long cep_key = get_block_formatted_cep(block);
    char *cep = get_block_cep(block);
    
    QDC_x1 = get_rect_x(block_rect);
    QDC_y1 = get_rect_y(block_rect);
    QDC_h = get_rect_height(block_rect); 
    QDC_w = get_rect_width(block_rect);

    set_id(cep);
    type_rect block_rect_del = delete_item_in_hash_table(QDC_blocks_table, get_key_from_block(block_rect), (void*)get_key_from_block, (void*)verify_block_found);
    insert_item_at_the_end_of_list(QDC_blocks_to_delete, block_rect_del);

    _report_block_txt_(block_rect_del);
    return;
}

type_mMlavltree delete_blocks_from_blocks_avl(type_mMlavltree blocks_avl, type_list list_of_blocks){
    int done;
    type_rect rect;
    type_block block_data;
    if(empty_list(list_of_blocks)){
        destroi_list(list_of_blocks);
        return blocks_avl;
    }
    set_current_to_last_item_in_list(list_of_blocks);
    do{
        done = is_current_first_item_in_list(list_of_blocks);
        rect = get_current_item_in_list(list_of_blocks);

        blocks_avl = delete_item_in_mMl_avl_tree(blocks_avl, rect, (void*)compare_rectangles_by_x_coordinate, (void*)compare_rect_blocks_cep);
        block_data = get_rect_data(rect);
        remove_block(block_data);
        destroi_rectangle(rect);
        delete_current_item_in_list(list_of_blocks);
    }while(!done);
    destroi_list(list_of_blocks);
    
    return blocks_avl;
}

type_list QDC_vertex_to_delete;
type_list QDC_edges_to_delete;
type_rect QDC_surronding_rect = NULL;

void action_catac_vertex(type_vertex vertex){
    char *id = get_vertex_id(vertex);
    
    insert_item_at_the_end_of_list(QDC_vertex_to_delete, id);
    _report_vertex_txt_(vertex);
}

long condition_catac_vertex(type_vertex vertex){
    double x = get_vertex_x(vertex);
    double y = get_vertex_y(vertex);

    return (long)point_in_rect(QDC_surronding_rect, x, y);
}

void deallocate_edge_and_report_edge(type_edge edge){
    _report_edge_txt_(edge);
    destroi_edge(edge);
}

void delete_vertex_from_graph_catac(type_graph via_graph, type_list list_of_vertex){
    int done;
    type_vertex vertex;
    type_block block_data;
    if(empty_list(list_of_vertex)){
        destroi_list(list_of_vertex);
        return;
    }
    set_current_to_last_item_in_list(list_of_vertex);
    do{
        done = is_current_first_item_in_list(list_of_vertex);
        vertex = get_current_item_in_list(list_of_vertex);
        char* vertexid = get_vertex_id(vertex);
        remove_vertex_from_graph(via_graph, vertexid, (void*)deallocate_edge_and_report_edge);

        destroi_vertex(vertex);

        delete_current_item_in_list(list_of_vertex);
    }while(!done);
    destroi_list(list_of_vertex);
}

// Remover as quadras contidas na região
// delimitada pelo retângulo x,y,w,h. Arestas
// incidentes em vértices dentro do retângulo
// especificado devem ser removidas.
// TXT: imprimir identificadores e dados
// associados a tudo o que foi removido.
// SVG: elementos removidos não devem aparecer.
// Desenhar sob o mapa o referido retângulo com
// cor de preenchimento #AB37C8, cor de borda
// #AA0044 e com 50% de transparência
// se pelo menos um dos vértices da aresta estiver dentro da área do catac, 
// a gente vai remover essa aresta, não vai remover o vértice e 
// no svg a gente pode printar o vértice boiando, é isso? SIM
type_mMlavltree catac(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_hashtable, type_graph via_graph, double x, double y, double w, double h){

    QDC_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);

    QDC_blocks_avl = blocks_avl;
    QDC_blocks_table = blocks_hashtable;
    QDC_blocks_to_delete = create_list();
    QDC_vertex_to_delete = create_list();


    set_x1_x2_y1_y2(x, x+w, y, y+h);
    traverse_mMlavltree_with_conditional_action(blocks_avl, (void*)traverse_side_rect_in_rect_, (void*)condition_rect_in_rect_, (void*)action_catac_blocks);    

    blocks_avl = delete_blocks_from_blocks_avl(blocks_avl, QDC_blocks_to_delete);
    insert_rectangle_with_different_opacity_in_svg(QDC_SVGFILE, x, y, w, h, "#AB37C8", "#AA0044", 0.5, 2);
    
    QDC_surronding_rect = new_rectangle("", x, y, w, h, "", "");

    traverse_verticies_with_conditional_action_graph(via_graph, (void*)action_catac_vertex, (void*)condition_catac_vertex);

    delete_vertex_from_graph_catac(via_graph, QDC_vertex_to_delete);
    return blocks_avl;
}