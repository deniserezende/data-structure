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

type_mMlavltree get_qry_input_and_generate_output(char *qryfilename, char *output_path, char *geo_filename, type_txt txtfile, type_svg svgfile, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable people_table, type_hashtable properties_leases, double viewbox[4]){
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
    char *sfx = (char*)malloc(40 * sizeof(char));

    char cardinal_direction;
    int house_number;
    double property_area, monthly_rent;
    double x, y, w, h;

    type_svg svg_temp_file = start_new_svg_file("deniserezendeqrytempfile.svg"); // file to store temp data
    
    while(!feof(qryfile)){ 
        fscanf(qryfile, "\n%[^\n]\ns", line);

        if(strncmp(line, "del", 3) == 0){
            sscanf(line, "%s %s", helper, cep);
            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEL<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
            blocks_avl = del(svg_temp_file, txtfile, blocks_avl, blocks_table, properties_table, people_table, properties_leases, cep, viewbox);
            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
        }
        else if(strncmp(line, "m?", 2) == 0){
                sscanf(line, "%s %s", helper, cep);
                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>M?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                m_(txtfile, blocks_table, properties_table, cep);
                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
            }
            else if(strncmp(line, "dm?", 3) == 0){
                    sscanf(line, "%s %s", helper, cpf);
                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DM?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                    dm_(svg_temp_file, txtfile, blocks_table, people_table, cpf, viewbox);
                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                }
                else if(strncmp(line, "mud", 3) == 0){
                        sscanf(line, "%s %s %s %c %d %s", helper, cpf, cep, &cardinal_direction, &house_number, additional_data);
                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MUD<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                        mud(svg_temp_file, txtfile, blocks_table, people_table, properties_table, cpf, cep, cardinal_direction, house_number, additional_data);
                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                    }
                    else if(strncmp(line, "oloc ", 5) == 0){
                            sscanf(line, "%s %s %s %c %d %s %lf %lf", helper, property_lease_id, cep, &cardinal_direction, &house_number, additional_data, &property_area, &monthly_rent); 
                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>OLOC<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                            oloc(properties_leases, property_lease_id, cep, cardinal_direction, house_number, additional_data, property_area, monthly_rent);
                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");            
                        }
                        else if(strncmp(line, "oloc?", 5) == 0){
                                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>OLOC?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                oloc_(svg_temp_file, txtfile, blocks_avl, properties_leases, x, y, w, h);
                                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                }
                                else if(strncmp(line, "loc ", 4) == 0){
                                    sscanf(line, "%s %s %s", helper, property_lease_id, cpf);
                                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>LOC<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                    loc(svg_temp_file, txtfile, blocks_table, properties_leases, people_table, property_lease_id, cpf, viewbox);
                                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                    }
                                    else if(strncmp(line, "loc?", 4) == 0){
                                        sscanf(line, "%s %s", helper, property_lease_id);
                                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>LOC?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                        loc_(svg_temp_file, txtfile, blocks_table, properties_leases, property_lease_id);
                                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                        }
                                        else if(strncmp(line, "dloc", 4) == 0){
                                            sscanf(line, "%s %s", helper, property_lease_id);
                                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DLOC<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                            dloc(txtfile, blocks_table, properties_leases, property_lease_id, viewbox);
                                              insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                            }
                                            else if(strncmp(line, "hom", 3) == 0){
                                                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HOM<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                hom(svg_temp_file, txtfile, blocks_avl, properties_table, properties_leases, x, y, w, h);
                                                insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                }
                                                else if(strncmp(line, "mul", 3) == 0){
                                                    sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MUL<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                    mul(svg_temp_file, txtfile, blocks_avl, properties_table, properties_leases, x, y, w, h);
                                                    insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                    }
                                                    else if(strncmp(line, "dmpt", 4) == 0){
                                                        sscanf(line, "%s %s", helper, sfx);
                                                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DMPT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                        char* dotfullpath = get_dot_fullpath(sfx, output_path, geo_filename);
                                                        type_dot dotfile = begin_design(dotfullpath);
                                                        dmpt(dotfile, blocks_avl);
                                                        end_design(dotfile);
                                                        free(dotfullpath);
                                                        insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                        }
                                                        else if(strncmp(line, "catac", 5) == 0){
                                                            sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CATAC<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                            blocks_avl = catac(svg_temp_file, txtfile, blocks_avl, blocks_table, properties_table, properties_leases, people_table, x, y, w, h);
                                                            insert_string_in_txt(txtfile, "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                                                        }
  
        // "Resets" the string
        strcpy(line, "\0");
    }

    end_svg_file(svg_temp_file);
    insert_blocks_in_svg(svgfile, blocks_avl);
    insert_svg_file_in_other_svg_file("deniserezendeqrytempfile.svg", svgfile);
    remove("deniserezendeqrytempfile.svg");

    free(line);
    free(helper);
    free(cep);
    free(cpf);
    free(additional_data);
    free(property_lease_id);
    free(sfx);
    fclose(qryfile);
    return(blocks_avl);
}


