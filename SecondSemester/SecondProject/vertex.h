#ifndef vertex_h
#define vertex_h

typedef void* type_vertex;

type_vertex new_vertex(char id[], double x, double y);

char* get_vertex_id(type_vertex vertex);

double get_vertex_x(type_vertex vertex);

double get_vertex_y(type_vertex vertex);

void destroi_vertex(type_vertex vertex);

#endif 



