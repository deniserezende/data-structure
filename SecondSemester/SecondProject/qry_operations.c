//
//  qryoperations.c 
//  
//
//  Created by Denise F. de Rezende on 25/05/21.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "qry_operations.h" 


char *get_dot_fullpath(char *dot_filename_without_extension, char *output_path, char *geo_filename){
    char *dot_fullpath;
    char *geo_filename_without_suffix = get_filename_without_suffix(geo_filename);
    if(dot_filename_without_extension == NULL) return NULL;
    char* dot_filename = malloc(sizeof(char) * (strlen(dot_filename_without_extension) + strlen(dot_filename_without_extension) + 7));
    sprintf(dot_filename, "%s-%s.dot%c", geo_filename_without_suffix, dot_filename_without_extension, '\0');
    dot_fullpath = concat_path_filename(output_path, dot_filename); 
    free(dot_filename);
    free(geo_filename_without_suffix);
    return dot_fullpath;
}

type_mMlavltree get_qry_input_and_generate_output(char *qryfilename, char *output_path, char *geo_filename, type_txt txtfile, type_svg svgfile, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_graph via_graph, double viewbox[4]){
    FILE *qryfile = fopen(qryfilename, "r");
    if (qryfile == NULL) {
        return NULL;
    }
    char *line = (char*)malloc(80 * sizeof(char));
    char *helper = (char*)malloc(10 * sizeof(char));
    char *cep = (char*)malloc(40 * sizeof(char));
    char *cpf = (char*)malloc(40 * sizeof(char));
    char *additional_data = (char*)malloc(40 * sizeof(char));
    char *property_lease_id = (char*)malloc(40 * sizeof(char));
    char *fastest_route_color = (char*)malloc(40 * sizeof(char));
    char *shortest_route_color = (char*)malloc(40 * sizeof(char));

    char cardinal_direction;
    int house_number;
    double x, y, w, h, f, limiar;
    type_property property = NULL;

    type_svg svg_temp_file = start_new_svg_file("deniserezendeqrytempfile.svg"); // file to store temp data
    
    while(!feof(qryfile)){ 
        fscanf(qryfile, "\n%[^\n]\ns", line);

        if(strncmp(line, "@o?", 3) == 0){ 
            sscanf(line, "%s %s %c %d", helper, cep, &cardinal_direction, &house_number);
            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>@o?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
            property = o_(svg_temp_file, txtfile, blocks_table, cep, cardinal_direction, house_number, viewbox);
            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
        }
        else if(strncmp(line, "catac", 5) == 0){
                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>catac<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                blocks_avl = catac(svg_temp_file, txtfile, blocks_avl, blocks_table, via_graph, x, y, w, h);
                printf("catac falta detalhes\n");
                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
            }
            else if(strncmp(line, "rv", 2) == 0){
                    sscanf(line, "%s %lf %lf %lf %lf %lf", helper, &x, &y, &w, &h, &f);
                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>rv<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                    rv(svg_temp_file, txtfile, via_graph, x, y, w, h, f);
                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                }
                else if(strncmp(line, "cx", 2) == 0){
                        sscanf(line, "%s %lf", helper, &limiar);
                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>cx<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                        cx(svg_temp_file, txtfile, via_graph, limiar);

                        printf("cx fim implementado\n");
                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                    }
                    else if(strncmp(line, "p?", 2) == 0){ //cep face num cmc cmr
                            sscanf(line, "%s %s %c %d %s %s", helper, cep, &cardinal_direction, &house_number, shortest_route_color, fastest_route_color); 
                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>p?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");

                            if(property != NULL) p_(svg_temp_file, txtfile, blocks_avl, blocks_table, via_graph, property, cep, cardinal_direction, house_number, shortest_route_color, fastest_route_color);
                            else printf("Não foi chamado o @o antes do p?");
                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");            
                        }
  
        // "Resets" the string
        strcpy(line, "\0");
    }
    printf("SVGTIME\n\n\n");

    end_svg_file(svg_temp_file);
    insert_blocks_in_svg(svgfile, blocks_avl);
    insert_via_in_svg(svgfile, via_graph);
    insert_svg_file_in_other_svg_file("deniserezendeqrytempfile.svg", svgfile);
    remove("deniserezendeqrytempfile.svg");

    printf("coloquei tudo\n");
    free(line);
    free(helper);
    free(cep);
    free(cpf);
    free(additional_data);
    free(property_lease_id);
    fclose(qryfile);
    return(blocks_avl);
}


