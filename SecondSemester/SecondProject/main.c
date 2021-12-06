#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "commandline.h"
#include "path.h"
#include "geo_operations.h"
#include "via_operations.h"
#include "graph.h"
#include "mM_avl_tree_wlist.h"
#include "hash_table.h"
#include "output_svg.h"
#include "qry_operations.h"
#include "vertex.h"
#include "edge.h"

#define DEFAULT_VIEW_BOX_V 50

char *get_one_named_svg_fullpath(char *filename, char *output_path);
char *get_geo_fullpath(char *geo_filename, char *input_path);
char *get_via_fullpath(char *via_filename, char *input_path);
char *get_qry_fullpath(char *qry_filename, char *input_path);
char *get_txt_and_svg_filename(char *geo_filename, char *qry_filename);
char *get_txt_fullpath(char *geo_filename, char *qry_filename, char *output_path);
char *get_two_named_svg_fullpath(char *filename1, char *filename2, char *output_path);

void deallocate_cityblocks_avl(type_rect rect_block);
void deallocate_cityblocks_hashtable(type_rect rect_block);
void deallocate_vertex(type_vertex vertex);
void deallocate_edge(type_edge edge);


int main(int argc, char *argv[]) {
    char *input_path = NULL;
    char *geo_filename = NULL;
    char *qry_filename = NULL;
    char *via_filename = NULL;
    char *output_path = NULL;

    char *via_fullpath = NULL;
    char *geo_fullpath = NULL;
    char *geo_svg_fullpath = NULL;
    char *via_svg_fullpath = NULL;
    char *qry_fullpath = NULL;
    char *txt_fullpath = NULL;
    char *second_svg_fullpath = NULL;

    double* viewbox_geo = malloc(sizeof(double) * 4);
    double* viewbox_via = malloc(sizeof(double) * 4);

    type_graph via_graph = create_graph();
    type_hashtable cityblocks_hashtable = create_hash_table();
    type_mMlavltree cityblocks_avl = create_mMl_avl_tree();

    // --------------------------------------------------- COMMAND LINE -----------------------------------------------
    commandline(argc, argv, &input_path, &geo_filename, &qry_filename, &via_filename, &output_path);

    // --------------------------------------------------- VIA FILE ---------------------------------------------------
    via_fullpath = get_via_fullpath(via_filename, input_path);
    if(via_fullpath != NULL) get_via_input(via_fullpath, via_graph, viewbox_via);

    // --------------------------------------------------- GEO FILE ---------------------------------------------------
    geo_fullpath = get_geo_fullpath(geo_filename, input_path);
    cityblocks_avl = get_geo_input(geo_fullpath, cityblocks_avl, cityblocks_hashtable, viewbox_geo);

    // --------------------------------------------------- OUTPUT FILE SVG 1 ---------------------------------------------------    
    char* my_name = (char*)malloc(sizeof(char) * 17);
    sprintf(my_name, "Denise Rezende%c", '\0');

    // Getting full path for the first output file
    geo_svg_fullpath = get_one_named_svg_fullpath(geo_filename, output_path);
   
    // Creating svg output file based on .geo
    type_svg geo_svgfile = start_new_svg_file_with_viewbox(geo_svg_fullpath, viewbox_geo[0] - DEFAULT_VIEW_BOX_V, viewbox_geo[1] - DEFAULT_VIEW_BOX_V, viewbox_geo[2]-viewbox_geo[0]+2*DEFAULT_VIEW_BOX_V, viewbox_geo[3]-viewbox_geo[1]+2*DEFAULT_VIEW_BOX_V);
    insert_comment_in_svg(geo_svgfile, my_name);
    insert_blocks_in_svg(geo_svgfile, cityblocks_avl);
    end_svg_file(geo_svgfile);

    // Getting full path for the second output file
    via_svg_fullpath = get_two_named_svg_fullpath(geo_filename, via_filename, output_path);

    // Creating svg output file based on .via
    type_svg via_svgfile = start_new_svg_file_with_viewbox(via_svg_fullpath, viewbox_via[0] - DEFAULT_VIEW_BOX_V, viewbox_via[1] - DEFAULT_VIEW_BOX_V, viewbox_via[2]-viewbox_via[0]+2*DEFAULT_VIEW_BOX_V, viewbox_via[3]-viewbox_via[1]+2*DEFAULT_VIEW_BOX_V);
    insert_comment_in_svg(via_svgfile, my_name);
    insert_via_in_svg(via_svgfile, via_graph);
    end_svg_file(via_svgfile);

    // --------------------------------------- QRY FILE AND OTHER OUTPUT FILES -------------------------------------------
    qry_fullpath = get_qry_fullpath(qry_filename, input_path);

    if(qry_fullpath != NULL){
        // Getting fullpath for the txt and svg (output files)
        txt_fullpath = get_txt_fullpath(geo_filename, qry_filename, output_path);
        second_svg_fullpath = get_two_named_svg_fullpath(geo_filename, qry_filename, output_path);

        // Starting both output files
        type_svg qry_svgfile = start_new_svg_file_with_viewbox(second_svg_fullpath, viewbox_via[0] - DEFAULT_VIEW_BOX_V, viewbox_via[1] - DEFAULT_VIEW_BOX_V, viewbox_via[2]-viewbox_via[0]+2*DEFAULT_VIEW_BOX_V, viewbox_via[3]-viewbox_via[1]+2*DEFAULT_VIEW_BOX_V);
        type_txt txtfile = start_new_txt_file(txt_fullpath);
        insert_string_in_txt(txtfile, my_name);
        insert_comment_in_svg(qry_svgfile, my_name);
        
        // Calling function to deal with qryfile
        cityblocks_avl = get_qry_input_and_generate_output(qry_fullpath, output_path, geo_filename, txtfile, qry_svgfile, cityblocks_avl, cityblocks_hashtable, via_graph, viewbox_via);

        // Ending output files
        end_svg_file(qry_svgfile);
        end_txt_file(txtfile);

        // Clean up
        free(txt_fullpath);
        free(second_svg_fullpath);
        if(qry_fullpath != NULL && strcmp(qry_fullpath, qry_filename) != 0) free(qry_fullpath);
        free(qry_filename);
    }

    // Clean up
    if(input_path != NULL) free(input_path);

    if(geo_fullpath != NULL && strcmp(geo_fullpath, geo_filename) != 0) free(geo_fullpath);
    if(geo_filename != NULL) free(geo_filename);
    if(geo_svg_fullpath != NULL) free(geo_svg_fullpath);
    if(via_svg_fullpath != NULL) free(via_svg_fullpath);

    if(via_fullpath != NULL && strcmp(via_fullpath, via_filename) != 0) free(via_fullpath);
    if(via_filename != NULL) free(via_filename);
    if(output_path != NULL) free(output_path);

    if(viewbox_geo != NULL) free(viewbox_geo);
    if(viewbox_via != NULL) free(viewbox_via);

    // DEALOCATING
    destroi_graph(via_graph, (void*)deallocate_vertex, (void*)deallocate_edge);
    destroi_hash_table(cityblocks_hashtable, (void*)deallocate_cityblocks_hashtable);
    destroi_mMl_avl_tree(cityblocks_avl, (void*)deallocate_cityblocks_avl);
}

void deallocate_cityblocks_avl(type_rect rect_block){
    type_block block = get_rect_data(rect_block);
    remove_block(block);
    destroi_rectangle(rect_block); 
}


void deallocate_cityblocks_hashtable(type_rect rect_block){
    // Since I will delete all rectangles in destroi_mMl_avl_tree() function
    // no need to delete them here!
    // type_block block = get_rect_data(rect_block);
    // remove_block(block);
    // destroi_rectangle(rect_block);
    return;
}

void deallocate_vertex(type_vertex vertex){
    destroi_vertex(vertex);
}

void deallocate_edge(type_edge edge){
    destroi_edge(edge);
}


char *get_one_named_svg_fullpath(char *filename, char *output_path){
    char *suffix = (char*)malloc(sizeof(char) * 5);
    char *svg_without_suffix = get_filename_without_suffix(filename);
    char *svg_filename, *svg_fullpath;
    sprintf(suffix, "%s", ".svg");
    svg_filename = concat_name_suffix(svg_without_suffix, suffix);
    if(output_path == NULL){
        free(suffix);
        free(svg_without_suffix);
        return svg_filename;
    }
    svg_fullpath = concat_path_filename(output_path, svg_filename);  
    free(suffix);
    free(svg_without_suffix);
    free(svg_filename);
    return svg_fullpath;
}

char *get_geo_fullpath(char *geo_filename, char *input_path){
    char *geo_fullpath;
    if(input_path == NULL) return geo_filename;
    geo_fullpath = concat_path_filename(input_path, geo_filename);  
    return geo_fullpath;
}


char *get_via_fullpath(char *via_filename, char *input_path){
    char *via_fullpath;
    if(input_path == NULL) return via_filename;
    if(via_filename == NULL) return NULL;
    via_fullpath = concat_path_filename(input_path, via_filename); 
    return via_fullpath;
}

char *get_qry_fullpath(char *qry_filename, char *input_path){
    char *qry_fullpath;
    if(input_path == NULL) return qry_filename;
    if(qry_filename == NULL) return NULL;
    qry_fullpath = concat_path_filename(input_path, qry_filename); 
    return qry_fullpath;
}

char *get_txt_and_svg_filename(char *filename1, char *filename2){
    char *geo_without_suffix = get_filename_without_suffix(basename(filename1));
    char *qry_without_suffix = get_filename_without_suffix(basename(filename2));
    char *filename_without_suffix = (char*)malloc(sizeof(char) * (strlen(geo_without_suffix) + strlen(qry_without_suffix) + 2)); //+2?
    sprintf(filename_without_suffix, "%s%s%s", geo_without_suffix, "-", qry_without_suffix);
    free(geo_without_suffix);
    free(qry_without_suffix);
    return filename_without_suffix;
}

char *get_txt_fullpath(char *geo_filename, char *qry_filename, char *output_path){
    char *suffix = (char*)malloc(sizeof(char) * 5);
    sprintf(suffix, "%s", ".txt");
    char* filename_without_suffix = get_txt_and_svg_filename(geo_filename, qry_filename);    
    char* txt_filename = concat_name_suffix(filename_without_suffix, suffix);
    char* txt_fullpath = concat_path_filename(output_path, txt_filename);
    free(suffix);
    free(filename_without_suffix);
    free(txt_filename);
    return txt_fullpath;
}

char *get_two_named_svg_fullpath(char *filename1, char *filename2, char *output_path){
    char *suffix = (char*)malloc(sizeof(char) * 5);
    sprintf(suffix, "%s", ".svg");
    char* filename_without_suffix = get_txt_and_svg_filename(filename1, filename2);    
    char* svg_filename = concat_name_suffix(filename_without_suffix, suffix);
    if(output_path == NULL){
        free(suffix);
        free(filename_without_suffix);
        return svg_filename;         
    }
    char* svg_fullpath = concat_path_filename(output_path, svg_filename);
    free(suffix);
    free(filename_without_suffix);
    free(svg_filename);
    return svg_fullpath;
}





