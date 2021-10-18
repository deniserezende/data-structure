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

double GO_minx, GO_maxx, GO_miny, GO_maxy;

void save_min_and_max(double x, double y, double x2, double y2){
    if(x2 >= GO_maxx) GO_maxx = x2;
    if(x <= GO_minx) GO_minx = x;
    if(y2 >= GO_maxy) GO_maxy = y2;
    if(y <= GO_miny) GO_miny = y;
}

type_mMlavltree get_geo_input(char *filename, type_mMlavltree cityblocks_tree, type_hashtable cityblocks_table, double view_box[4]){
    FILE *geofile = fopen(filename, "r");
    if(geofile == NULL){
        return NULL;
    }

    //AQUIDE rever valores
    GO_minx = 100000;
    GO_maxx = 0;
    GO_miny = 100000;
    GO_maxy = 0;

    char *line = malloc(80 * sizeof(char));
    char *helper = malloc(3 *sizeof(char));
    char *helper2 = malloc(3 *sizeof(char));
    char *cep = malloc(40 *sizeof(char));
    char *fill_color = malloc(40 *sizeof(char));
    char *stroke_color = malloc(40 *sizeof(char));

    double x, y, width, height;
    double stroke_width;

    type_rect block;
 
    // Creating a pointer to the function
    long(*compare_rects_x_ptr)(type_rect, type_rect);
    compare_rects_x_ptr = compare_rectangles_by_x_coordinate;

    // Creating a pointer to the function
    long(*get_rect_key_ptr)(type_rect);
    get_rect_key_ptr = get_key_from_block;

    // Creating a pointer to the function
    long(*compare_rect_blocks_cep_ptr)(type_rect, type_rect);
    compare_rect_blocks_cep_ptr = compare_rect_blocks_cep;

    while(!feof(geofile)){
        fscanf(geofile, "\n%[^\n]s\n", line);
        
        if(strncmp(line, "cq", 2) == 0){
            sscanf(line, "%s %lf%s %s %s", helper, &stroke_width, helper2, fill_color, stroke_color);
        }
        else if(strncmp(line, "q", 1) == 0){
                sscanf(line, "%s %s %lf %lf %lf %lf", helper, cep, &x, &y, &width, &height);
                save_min_and_max(x, y, x+width, y+height);

                type_block block_data = new_block(cep);
                block = new_rectangle(cep, x, y, width, height, stroke_color, fill_color);
                add_rectangles_stroke_width(block, stroke_width);
                insert_data_in_rect(block, block_data);

                insert_item_in_hash_table(cityblocks_table, block,  get_key_from_block(block), (void*)get_rect_key_ptr, (void*)compare_rect_blocks_cep_ptr);
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
    free(helper2);
    fclose(geofile);
    free(cep);
    free(stroke_color);
    free(fill_color);
    view_box[0] = GO_minx;
    view_box[1] = GO_miny;
    view_box[2] = GO_maxx;
    view_box[3] = GO_maxy;
    return cityblocks_tree;
}


