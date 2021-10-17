#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "commandline.h"
#include "path.h"
#include "pm_operations.h"
#include "geo_operations.h"
#include "qry_operations.h"
#include "hash_table.h"
#include "mM_avl_tree.h"
#include "output_svg.h"
#include "SVG.h"
#include "TXT.h"



char *get_first_svg_fullpath(char *geo_filename, char *output_path);
char *get_geo_fullpath(char *geo_filename, char *input_path);
char *get_pm_fullpath(char *pm_filename, char *input_path);
char *get_qry_fullpath(char *qry_filename, char *input_path);
char *get_txt_and_svg_filename(char *geo_filename, char *qry_filename);
char *get_txt_fullpath(char *geo_filename, char *qry_filename, char *output_path);
char *get_second_svg_fullpath(char *geo_filename, char *qry_filename, char *output_path);

// void print_item(type_rect rect){
//     type_rectdata data = get_rect_data(rect);
//     printf("cep=%s\n", get_property_cep(data));
// }


int main(int argc, char *argv[]) {
    char *input_path = NULL;
    char *geo_filename = NULL;
    char *qry_filename = NULL;
    char *pm_filename = NULL;
    char *output_path = NULL;

    char *pm_fullpath = NULL;
    char *geo_fullpath = NULL;
    char *first_svg_fullpath = NULL;
    char *qry_fullpath = NULL;
    char *txt_fullpath = NULL;
    char *second_svg_fullpath = NULL;
    type_hashtable people_hashtable = create_hash_table();
    type_hashtable properties_hashtable = create_hash_table();
    type_hashtable cityblocks_hashtable = create_hash_table();
    type_mMavltree cityblocks_avltree = create_mMl_avl_tree();
    type_mMavltree property_leases_hashtable = create_hash_table();


    // --------------------------------------------------- COMMAND LINE -----------------------------------------------
    commandline(argc, argv, &input_path, &geo_filename, &qry_filename, &pm_filename, &output_path);
    // printf("input_path = %s\n", input_path);
    // printf("geo_filename = %s\n", geo_filename);
    // printf("qry_filename = %s\n", qry_filename);
    // printf("pm_filename = %s\n", pm_filename);
    // printf("output_path = %s\n", output_path);


    // --------------------------------------------------- PM FILE ---------------------------------------------------
    pm_fullpath = get_pm_fullpath(pm_filename, input_path);
    if(pm_fullpath != NULL) get_pm_input(pm_fullpath, people_hashtable, properties_hashtable);
    // printf("fiz o pm\n");

    // --------------------------------------------------- GEO FILE ---------------------------------------------------
    geo_fullpath = get_geo_fullpath(geo_filename, input_path);
    cityblocks_avltree = get_geo_input(geo_fullpath, cityblocks_avltree, cityblocks_hashtable);
    // printf("fiz o geo\n");


    // --------------------------------------------------- OUTPUT FILE SVG 1 ---------------------------------------------------
    // Getting full path for the first output file
    first_svg_fullpath = get_first_svg_fullpath(geo_filename, output_path);
    char* my_name = (char*)malloc(sizeof(char) * 17);
    sprintf(my_name, "Denise Rezende%c", '\0');

    // Creating svg output file
    type_svg svgfile = start_new_svg_file(first_svg_fullpath);
    insert_comment_in_svg(svgfile, my_name);
    insert_blocks_in_svg(svgfile, cityblocks_avltree);
    end_svg_file(svgfile);
    // printf("fiz o svg 1\n");


    // void(*get_print_item)(type_rect);
    // get_print_item = print_item;


    //preorder_debug_fuction_mMlavltree(cityblocks_avltree, (void*)get_print_item);


    // --------------------------------------- QRY FILE AND OTHER OUTPUT FILES -------------------------------------------
    qry_fullpath = get_qry_fullpath(qry_filename, input_path);

    if(qry_fullpath != NULL){
        // Getting fullpath for the txt and svg (output files)
        txt_fullpath = get_txt_fullpath(geo_filename, qry_filename, output_path);
        second_svg_fullpath = get_second_svg_fullpath(geo_filename, qry_filename, output_path);
        
        // Starting both output files
        type_svg svgfile2 = start_new_svg_file(second_svg_fullpath);
        type_txt txtfile = start_new_txt_file(txt_fullpath);
        insert_string_in_txt(txtfile, my_name);
        insert_comment_in_svg(svgfile2, my_name);
        
        // Calling function to deal with qryfile
        cityblocks_avltree = get_qry_input_and_generate_output(qry_fullpath, output_path, geo_filename, txtfile, svgfile2, cityblocks_avltree, cityblocks_hashtable, properties_hashtable, people_hashtable, property_leases_hashtable);
        
        // Ending output files
        end_svg_file(svgfile2);
        end_txt_file(txtfile);

        free(txt_fullpath);
        free(second_svg_fullpath);
        free(qry_fullpath);
    }


    free(geo_fullpath);
    free(first_svg_fullpath);
}


char *get_first_svg_fullpath(char *geo_filename, char *output_path){
    char *suffix = (char*)malloc(sizeof(char) * 5);
    char *svg_without_suffix = get_filename_without_suffix(geo_filename);
    char *svg_filename, *svg_fullpath;
    sprintf(suffix, "%s", ".svg");
    svg_filename = concat_name_suffix(svg_without_suffix, suffix);
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


char *get_pm_fullpath(char *pm_filename, char *input_path){
    char *pm_fullpath;
    if(input_path == NULL) return pm_filename;
    if(pm_filename == NULL) return NULL;
    pm_fullpath = concat_path_filename(input_path, pm_filename); 
    return pm_fullpath;
}

char *get_qry_fullpath(char *qry_filename, char *input_path){
    char *qry_fullpath;
    if(input_path == NULL) return qry_filename;
    if(qry_filename == NULL) return NULL;
    qry_fullpath = concat_path_filename(input_path, qry_filename); 
    return qry_fullpath;
}

char *get_txt_and_svg_filename(char *geo_filename, char *qry_filename){
    char *geo_without_suffix = get_filename_without_suffix(basename(geo_filename));
    char *qry_without_suffix = get_filename_without_suffix(basename(qry_filename));
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

char *get_second_svg_fullpath(char *geo_filename, char *qry_filename, char *output_path){
    char *suffix = (char*)malloc(sizeof(char) * 5);
    sprintf(suffix, "%s", ".svg");
    char* filename_without_suffix = get_txt_and_svg_filename(geo_filename, qry_filename);    
    char* svg_filename = concat_name_suffix(filename_without_suffix, suffix);
    char* svg_fullpath = concat_path_filename(output_path, svg_filename);
    free(suffix);
    free(filename_without_suffix);
    free(svg_filename);
    return svg_fullpath;
}





