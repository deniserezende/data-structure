#include "qry_p_.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// AQUIDE verificar se em ponteiros não estou passando double!

type_svg QP_SVGFILE;

long _get_fastest_route_time(type_edge edge){
    double length = get_edge_length(edge);
    double speed_limit = get_edge_speed_limit(edge);
    long time = (long)(length/speed_limit);
    return (long)time;
}

long _get_edge_length(type_edge edge){
    double length = get_edge_length(edge);
    return (long)length;
}


void find_minimum_distance_to_property(type_hashtable cityblocks_hash, type_property property, double minimum_distance_point[2]){
    char* cep = get_property_cep(property);
    //long cep_key = get_property_cep_key(property);
    long cep_key = format_cep_from_base36_to_base10(cep);

    set_id(cep);
    type_hashitem block = lookup_item_in_hash_table(cityblocks_hash, cep_key, (void*)get_key_from_block, (void*)verify_block_found);
    if(block == NULL){
        printf("vish! Block == NULL\n");
    }
    double x = get_rect_x(block);
    double y = get_rect_y(block);
    double w = get_rect_width(block);
    double h = get_rect_height(block);


    int house_number = get_property_house_number(property);
    char cardinal_direction = get_property_cardinal_direction(property);

    int shift_amount_x = 0;
    int shift_amount_y = 0;
    switch (cardinal_direction) {
    case 'N':
        shift_amount_x = house_number;
        shift_amount_y = h;
        break;
    case 'S':
        shift_amount_x = house_number;
        shift_amount_y = 0;
        break;
    case 'L':
        shift_amount_x = 0;
        shift_amount_y = house_number;
        break;
    case 'O':
        shift_amount_x = w;
        shift_amount_y = house_number;
        break;
    default:
        break;
    }

    double dist = __INT_MAX__;

    double dist_one = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x, y);
    if(dist_one < dist){
        dist = dist_one;
        minimum_distance_point[0] = x;
        minimum_distance_point[1] = y;
    }
    double dist_two = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x, y+h);
    if(dist_two < dist){
        dist = dist_two;
        minimum_distance_point[0] = x;
        minimum_distance_point[1] = y+h;
    }
    double dist_three = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x+w, y);
    if(dist_three < dist){
        dist = dist_three;
        minimum_distance_point[0] = x+w;
        minimum_distance_point[1] = y;
    }
    double dist_four = distance_between_two_points(x+shift_amount_x, y+shift_amount_y, x+w, y+h);
    if(dist_four < dist){
        dist = dist_four;
        minimum_distance_point[0] = x+w;
        minimum_distance_point[1] = y+h;  
    }
}

double QP_minimum_distance_point[2];
type_vertex QP_origin_vertex = NULL, QP_destination_vertex = NULL;
double QP_dist;

//AQUIDE conferir isso aqui!!!!!!!!!!!!!
// x <= ??? x == ????
long traverse_condition_p_(type_vertex vertex){
    double x = get_vertex_x(vertex);
    double y = get_vertex_y(vertex);

    double dist = distance_between_two_points(x, y, QP_minimum_distance_point[0], QP_minimum_distance_point[1]);

    if(dist < QP_dist){
        QP_dist = dist;
        return 1;
    }
    return 0;
}

void traverse_action_origin_p_(type_vertex vertex){
    QP_origin_vertex = vertex;
}

void traverse_action_destination_p_(type_vertex vertex){
    QP_destination_vertex = vertex;
}

void p_svg_output(type_list vertices, char color[], double stroke_width){
    int done;
    type_vertex vertex;
    if(empty_list(vertices)){
        printf("EMPTY LIST OF VERTICES REPRESENTING PATH\n");
        return;
    }
    set_current_to_last_item_in_list(vertices);
    vertex = get_current_item_in_list(vertices);
    
    if(is_current_first_item_in_list(vertices)){
        printf("Only one element\n");
        return;
    }
    
    double x = get_vertex_x(vertex);
    double y = get_vertex_y(vertex);
    double x2;
    double y2;

    move_current_backward_in_list(vertices);

    while(!is_current_first_item_in_list(vertices)){
        vertex = get_current_item_in_list(vertices);

        x2 = get_vertex_x(vertex);
        y2 = get_vertex_y(vertex);
        char* id = get_vertex_id(vertex);

        insert_line_in_svg(QP_SVGFILE, x, y, x2, y2, color, stroke_width);

        move_current_backward_in_list(vertices);
        x = x2;
        y = y2;
    }

    destroi_list(vertices);
}


// Qual o melhor trajeto de carro entre a origem
// (@o?) e o destino especificado pelo endereço
// cep/face/num. O percurso na representação
// pictórica deve indicar o trajeto mais curto na cor
// cmc e o trajeto mais rápido com a cor cmr.
// TXT: descrição textual do percurso
// SGV : traçar (linhas) dos percursos com as cores
// correspondentes. Cuidado para que uma
// percurso não esconda o outro. Indicar o início e
// o fim do percurso. As linhas devem ser grossas,
// mas menos espessas que as arestas da AGM
void p_(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_hashtable, type_graph via_graph, type_property origin_property, char cep[], char cardinal_direction, int house_number, char shortest_route_color[], char fastest_route_color[]){
    QP_SVGFILE = SVGFILE;
    // achar o vertice mais proximo da property
    // pegar o cep for no retangulo (pela hash) verificar o vertice mais proximo 

       // achar o vertice mais proximo da property

    // pegar o id desse vertice = source_id
    // achar o vertice mais proximo do cep dado
    // pegar o id desse vertice = destination_id
    double minimum_distance_point_origin[2];
    find_minimum_distance_to_property(blocks_hashtable, origin_property, minimum_distance_point_origin);
    
    QP_minimum_distance_point[0] = minimum_distance_point_origin[0];
    QP_minimum_distance_point[1] = minimum_distance_point_origin[1];
    QP_dist = __INT_MAX__;
    traverse_verticies_with_conditional_action_graph(via_graph, (void*)traverse_action_origin_p_, (void*)traverse_condition_p_);
    //AQUIDE destroi property?

    double minimum_distance_point_destination[2];
    type_property destination_property = new_property(cep, cardinal_direction, house_number, "");
    find_minimum_distance_to_property(blocks_hashtable, destination_property, minimum_distance_point_destination);

    QP_minimum_distance_point[0] = minimum_distance_point_destination[0];
    QP_minimum_distance_point[1] = minimum_distance_point_destination[1];
    QP_dist = __INT_MAX__;

    traverse_verticies_with_conditional_action_graph(via_graph, (void*)traverse_action_destination_p_, (void*)traverse_condition_p_);


    insert_circle_in_svg(SVGFILE, minimum_distance_point_origin[0], minimum_distance_point_origin[1], 10, "Black", "Black", 1);
    insert_circle_in_svg(SVGFILE, minimum_distance_point_destination[0], minimum_distance_point_destination[1], 10, "Pink", "Pink", 1);

    char *sourceid = get_vertex_id(QP_origin_vertex);
    char *destinationid = get_vertex_id(QP_destination_vertex);
    printf("sourceid=%s\n", sourceid);
    printf("destinationid=%s\n", destinationid);
    type_list shortest_solution = dijkstras_algorithm_with_destination_in_graph(via_graph, sourceid, destinationid, (void*)_get_edge_length);
    p_svg_output(shortest_solution, shortest_route_color, 4);

    type_list fastest_solution =  dijkstras_algorithm_with_destination_in_graph(via_graph, sourceid, destinationid, (void*)_get_fastest_route_time);
    p_svg_output(fastest_solution, fastest_route_color, 1);
} 

