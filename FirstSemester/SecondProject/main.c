//
//  main.c
//  
//
//  Created by Denise F. de Rezende on 25/05/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h> // This is a Linux library 
#include "commandline.h"
#include "path.h"
#include "geooperations.h"
#include "qryoperations.h"
#include "kd_tree.h"
#include "rectangle.h"
#include "circle.h"
#include "TXT.h"
#include "SVG.h"
#include "output_svg.h"

char *get_first_svg_fullpath(char *geo_filename, char *output_path);
char *get_geo_fullpath(char *geo_filename, char *input_path);
char *get_qry_fullpath(char *qry_filename, char *input_path);
char *get_txt_and_svg_filename(char *geo_filename, char *qry_filename);
char *get_txt_fullpath(char *geo_filename, char *qry_filename, char *output_path);
char *get_second_svg_fullpath(char *geo_filename, char *qry_filename, char *output_path);

int main(int argc, char *argv[]) {
    char *input_path = NULL;
    char *geo_filename = NULL;
    char *qry_filename = NULL;
    char *output_path = NULL;
    char *geo_fullpath = NULL;
    char *first_svg_fullpath = NULL;
    char *qry_fullpath = NULL;
    char *txt_fullpath = NULL;
    char *second_svg_fullpath = NULL;
    type_kdtree circles_kd = create_kdtree(2);
    type_kdtree rects_kd = create_kdtree(2);
    type_svg svgfile;
    type_svg svgfile2;
    type_txt txtfile;
    // --------------------------------------------------- COMMAND LINE -----------------------------------------------
    commandline(argc, argv, &input_path, &geo_filename, &qry_filename, &output_path);

    // --------------------------------------------------- GEO FILE ---------------------------------------------------
    geo_fullpath = get_geo_fullpath(geo_filename, input_path);
    read_geo_and_saves_info(geo_fullpath, &circles_kd, &rects_kd);

    // --------------------------------------------------- OUTPUT FILE SVG 1 ---------------------------------------------------
    // Getting full path for the first output file
    first_svg_fullpath = get_first_svg_fullpath(geo_filename, output_path);
    
    // Creating svg output file
    svgfile = start_new_svg_file(first_svg_fullpath);
    insert_comment_in_svg(svgfile, "Denise Rezende");  
    insert_rects_in_svg(svgfile, rects_kd);
    insert_circles_in_svg(svgfile, circles_kd);
    end_svg_file(svgfile);

    // --------------------------------------- QRY FILE AND OTHER OUTPUT FILES -------------------------------------------
    qry_fullpath = get_qry_fullpath(qry_filename, input_path);
    if(qry_fullpath != NULL){
        // Getting fullpath for the txt and svg (output files)
        txt_fullpath = get_txt_fullpath(geo_filename, qry_filename, output_path);
        second_svg_fullpath = get_second_svg_fullpath(geo_filename, qry_filename, output_path);
        
        // Starting both output files
        svgfile2 = start_new_svg_file(second_svg_fullpath);
        txtfile = start_new_txt_file(txt_fullpath);
        insert_string_in_txt(txtfile, "Denise Rezende");
        insert_comment_in_svg(svgfile2, "Denise Rezende");
        
        // Calling function to deal with qryfile
        read_qry_and_report_called_functions(qry_fullpath, txtfile, svgfile2, rects_kd, circles_kd);
        
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
    char *suffix = malloc(sizeof(char) * 5);
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
    char *filename_without_suffix = malloc(sizeof(char) * (strlen(geo_without_suffix) + strlen(qry_without_suffix) + 2)); //+2?
    sprintf(filename_without_suffix, "%s%s%s", geo_without_suffix, "-", qry_without_suffix);
    free(geo_without_suffix);
    free(qry_without_suffix);
    return filename_without_suffix;
}

char *get_txt_fullpath(char *geo_filename, char *qry_filename, char *output_path){
    char *suffix = malloc(sizeof(char) * 5);
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
    char *suffix = malloc(sizeof(char) * 5);
    sprintf(suffix, "%s", ".svg");
    char* filename_without_suffix = get_txt_and_svg_filename(geo_filename, qry_filename);    
    char* svg_filename = concat_name_suffix(filename_without_suffix, suffix);
    char* svg_fullpath = concat_path_filename(output_path, svg_filename);
    free(suffix);
    free(filename_without_suffix);
    free(svg_filename);
    return svg_fullpath;
}





