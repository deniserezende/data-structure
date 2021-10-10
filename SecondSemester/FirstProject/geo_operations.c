//
//  geo_operations.c
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geo_operations.h"

type_mMlavltree get_geo_input(char *filename, type_mMlavltree cityblocks_tree, type_hashtable cityblocks_table){
FILE *geofile = fopen(filename, "r");
    if(geofile == NULL){
        return NULL;
    }

    char *line = malloc(80 * sizeof(char));
    char *helper = malloc(3 *sizeof(char));
    char cep[40];
    double x, y, width, height;
    char fill_color[40], stroke_color[40];
    double stroke_width;

    type_rect block;
 
    // Creating a pointer to the function
    long(*compare_rects_x_ptr)(type_rect, type_rect);
    compare_rects_x_ptr = compare_rectangles_by_x_coordinate;

    // Creating a pointer to the function
    long(*get_rect_key_ptr)(type_rect);
    get_rect_key_ptr = get_key_from_block;

    while(!feof(geofile)){
        fscanf(geofile, "\n%[^\n]s\n", line);
        
        if(strncmp(line, "cq", 2) == 0){
            sscanf(line, "%s %lf %s %s", helper, &stroke_width, fill_color, stroke_color);
        }
        else if(strncmp(line, "q", 1) == 0){
                sscanf(line, "%s %s %lf %lf %lf %lf", helper, cep, &x, &y, &width, &height);
                
                type_block block_data = new_block(cep);
                block = new_rectangle(cep, x, y, width, height, stroke_color, fill_color);
                add_rectangles_stroke_width(block, stroke_width);
                insert_data_in_rect(block, block_data);

                insert_item_in_hash_table(cityblocks_table, block,  get_key_from_block(block), (void*)get_rect_key_ptr);
                cityblocks_tree = insert_item_in_mMl_avl_tree(cityblocks_tree, block, (void*)compare_rects_x_ptr);
                //adicionar uma lista e nao o bloco!
            }
            else if(strncmp(line, "nx", 2) == 0){
                // No need to do anything, because I don't use this data!
                }
                else break;
        // "Resets" the string
        strcpy(line, "\0");
    }

    free(line);
    free(helper);
    fclose(geofile);
    return cityblocks_tree;
}


