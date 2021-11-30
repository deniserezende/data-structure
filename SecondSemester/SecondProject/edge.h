#ifndef edge_h
#define edge_h

typedef void* type_edge;

type_edge new_edge(char id[], char id_vertex_one[], char id_vertex_two[], char cep_right_block[], char cep_left_block[], double edge_length,  double speed_limit);

char* get_edge_id(type_edge edge);

double get_edge_length(type_edge edge);

double get_edge_speed_limit(type_edge edge);

void set_edge_speed_limit(type_edge edge, double speed_limit);

void destroi_edge(type_edge edge);

#endif 



