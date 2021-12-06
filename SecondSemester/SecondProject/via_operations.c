#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "via_operations.h"

double VO_minx;
double VO_miny;
double VO_maxx;
double VO_maxy;

void save_min_and_max_via(double x, double y){
    if(x >= VO_maxx) VO_maxx = x;
    if(x <= VO_minx) VO_minx = x;
    if(y >= VO_maxy) VO_maxy = y;
    if(y <= VO_miny) VO_miny = y;
}

void get_via_input(char via_fullpath[], type_graph via_graph, double view_box[4]){
    FILE *viafile = fopen(via_fullpath, "r");

    if(viafile == NULL){
        return;
    }

    VO_minx = __INT_MAX__;
    VO_miny = __INT_MAX__;
    VO_maxx = 0;
    VO_maxy = 0;
   
    char *line = malloc(150 * sizeof(char));
    char *helper = malloc(3 *sizeof(char));
    char *id = malloc(40 *sizeof(char));
    char *id1 = malloc(40 *sizeof(char));
    char *id2 = malloc(40 *sizeof(char));
    char *ldir = malloc(40 *sizeof(char));
    char *lesq = malloc(40 *sizeof(char));
    char *fill_color = malloc(40 *sizeof(char));
    char *stroke_color = malloc(40 *sizeof(char));

    double x, y, length, speed;
    double stroke_width;

    while(!feof(viafile)){
        fscanf(viafile, "\n%[^\n]s\n", line);
        
        if(strncmp(line, "v", 1) == 0){
            sscanf(line, "%s %s %lf %lf", helper, id, &x, &y);
            save_min_and_max_via(x, y);
            type_vertex vertex = new_vertex(id, x, y);
            add_vertex_to_graph(via_graph, id);
            set_vertex_info_in_graph(via_graph, id, vertex);
        }
        else if(strncmp(line, "e", 1) == 0){
                sscanf(line, "%s %s %s %s %s %lf %lf %s", helper, id1, id2, ldir, lesq, &length, &speed, id);
                type_edge edge = new_edge(id, id1, id2, ldir, lesq, length, speed);
                add_edge_to_graph(via_graph, id1, id2);
                set_edge_info_in_graph(via_graph, id1, id2, edge);
            }
        // "Resets" the string
        strcpy(line, "\0");
    }

    free(line);
    free(helper);
    fclose(viafile);
    free(stroke_color);
    free(fill_color);
    free(id);
    free(id1);
    free(id2);
    free(ldir);
    free(lesq);

    // setting view_box so that the user can access values from main
    view_box[0] = VO_minx;
    view_box[1] = VO_miny;
    view_box[2] = VO_maxx;
    view_box[3] = VO_maxy;
}