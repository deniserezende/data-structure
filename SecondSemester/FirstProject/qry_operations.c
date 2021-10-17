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

void get_qry_input_and_generate_output(char *qryfilename, char *output_path, char *geo_filename, type_txt txtfile, type_svg svgfile, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable people_table, type_hashtable properties_leases){
    FILE *qryfile = fopen(qryfilename, "r");
    if (qryfile == NULL) {
        return;
    }
    char *line = (char*)malloc(70 * sizeof(char));
    char *helper = (char*)malloc(5 * sizeof(char));
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
        //printf("line=%s\n", line);

        if(strncmp(line, "del", 3) == 0){
            sscanf(line, "%s %s", helper, cep);
            insert_string_in_txt(txtfile, helper);
            blocks_avl = del(svg_temp_file, txtfile, blocks_avl, blocks_table, properties_table, people_table, properties_leases, cep);
        }
        else if(strncmp(line, "m?", 2) == 0){
                sscanf(line, "%s %s", helper, cep);
                insert_string_in_txt(txtfile, helper);
                m_(txtfile, blocks_table, properties_table, cep);
            }
            else if(strncmp(line, "dm?", 3) == 0 || strncmp(line, "fg\0", 3) == 0){
                    sscanf(line, "%s %s", helper, cpf);
                    insert_string_in_txt(txtfile, helper);
                    dm_(svg_temp_file, txtfile, blocks_table, people_table, cpf);
                    
                }
                else if(strncmp(line, "mud", 3) == 0){
                        printf("entrei no mud\n");
                        sscanf(line, "%s %s %s %c %d %s", helper, cpf, cep, &cardinal_direction, &house_number, additional_data);
                        insert_string_in_txt(txtfile, helper);
                        mud(svg_temp_file, txtfile, blocks_table, people_table, properties_table, cpf, cep, cardinal_direction, house_number, additional_data);
            
                    }
                    else if(strncmp(line, "oloc ", 5) == 0){
                            printf("entrei no oloc\n");
                            sscanf(line, "%s %s %s %c %d %s %lf %lf", helper, property_lease_id, cep, &cardinal_direction, &house_number, additional_data, &property_area, &monthly_rent); 
                            insert_string_in_txt(txtfile, helper);
                            oloc(properties_leases, property_lease_id, cep, cardinal_direction, house_number, additional_data, property_area, monthly_rent);
                            
                        }
                        else if(strncmp(line, "oloc?", 5) == 0){
                                printf("entrei no oloc?\n");
                                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                insert_string_in_txt(txtfile, helper);
                                oloc_(svg_temp_file, txtfile, blocks_avl, properties_leases, x, y, w, h);

                                }
                                else if(strncmp(line, "loc ", 4) == 0){
                                    printf("entrei no loc\n");
                                    sscanf(line, "%s %s %s", helper, property_lease_id, cpf);
                                    insert_string_in_txt(txtfile, helper);
                                    loc(svg_temp_file, txtfile, blocks_table, properties_leases, people_table, property_lease_id, cpf);
                    
                                    }
                                    else if(strncmp(line, "loc?", 4) == 0){
                                        sscanf(line, "%s %s", helper, property_lease_id);
                                        insert_string_in_txt(txtfile, helper);
                                        loc_(svg_temp_file, txtfile, blocks_table, properties_leases, property_lease_id);
                        
                                        }
                                        else if(strncmp(line, "dloc", 4) == 0){
                                            sscanf(line, "%s %s", helper, property_lease_id);
                                            insert_string_in_txt(txtfile, helper);
                                            dloc(txtfile, blocks_table, properties_leases, property_lease_id);
                            
                                            }
                                            else if(strncmp(line, "hom", 3) == 0){
                                                printf("entrei no hom\n");
                                                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                insert_string_in_txt(txtfile, helper);
                                                hom(svg_temp_file, txtfile, blocks_avl, properties_table, properties_leases, people_table, x, y, w, h);
                                
                                                }
                                                else if(strncmp(line, "mul", 3) == 0){
                                                    sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                    insert_string_in_txt(txtfile, helper);
                                                    mul(svg_temp_file, txtfile, blocks_avl, properties_table, properties_leases, people_table, x, y, w, h);
                                                    
                                    
                                                    }
                                                    else if(strncmp(line, "dmpt", 4) == 0){
                                                        printf("entrei no dmpt\n");
                                                        sscanf(line, "%s %s", helper, sfx);
                                                        insert_string_in_txt(txtfile, helper);
                                                        char* dotfullpath = get_dot_fullpath(sfx, output_path, geo_filename);
                                                        type_dot dotfile = begin_design(dotfullpath);
                                                        dmpt(dotfile, blocks_avl);
                                                        end_design(dotfile);
                                                        free(dotfullpath);
                                                        }
                                                        else if(strncmp(line, "catac", 5) == 0){
                                                            printf("entrei no catac\n");
                                                            sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                            insert_string_in_txt(txtfile, helper);
                                                            blocks_avl = catac(svg_temp_file, txtfile, blocks_avl, blocks_table, properties_table, properties_leases, people_table, x, y, w, h);
                                                        }
  
        // "Resets" the string
        strcpy(line, "\0");
    }

    end_svg_file(svg_temp_file);
    insert_blocks_in_svg(svgfile, blocks_avl);
    insert_svg_file_in_other_svg_file("deniserezendeqrytempfile.svg", svgfile);
    int removed = remove("deniserezendeqrytempfile.svg");
    printf("REMOVED = %d\n", removed);

    free(line);
    free(helper);
    free(cep);
    free(cpf);
    free(additional_data);
    free(property_lease_id);
    free(sfx);
    fclose(qryfile);
}


