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

void get_qry_input_and_generate_output(char *qryfilename, type_txt txtfile, type_svg svgfile, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable people_table, type_hashtable properties_leases){
    FILE *qryfile = fopen(qryfilename, "r");
    if (qryfile == NULL) {
        return;
    }
    char *line = (char*)malloc(60 * sizeof(char));
    char *helper = (char*)malloc(5 * sizeof(char));
    char cep[40], cpf[40], cardinal_direction, additional_data[40], property_lease_id[40];
    int house_number;
    char sfx[40];
    double property_area, monthly_rent;
    double x, y, w, h;

    type_hashtable property_leases = create_hash_table();
    
    while(!feof(qryfile)){ 
        fscanf(qryfile, "\n%[^\n]\ns", line);
        printf("line=%s\n", line);

        if(strncmp(line, "del", 3) == 0){
            sscanf(line, "%s %s", helper, cep);
            insert_string_in_txt(txtfile, helper);
            blocks_avl = del(svgfile, txtfile, blocks_avl, blocks_table, properties_table, people_table, properties_leases, cep);
        }
        else if(strncmp(line, "m?", 2) == 0){
                sscanf(line, "%s %s", helper, cep);
                insert_string_in_txt(txtfile, helper);
                m_(txtfile, blocks_table, properties_table, cep);
            }
            else if(strncmp(line, "dm?", 2) == 0 || strncmp(line, "fg\0", 3) == 0){
                    sscanf(line, "%s %s", helper, cpf);
                    insert_string_in_txt(txtfile, helper);
                    dm_(svgfile, txtfile, blocks_table, people_table, cpf);
                    
                }
                else if(strncmp(line, "mud", 3) == 0){
                        printf("entrei no mud\n");
                        sscanf(line, "%s %s %s %c %d %s", helper, cpf, cep, &cardinal_direction, &house_number, additional_data);
                        insert_string_in_txt(txtfile, helper);
                        mud(svgfile, txtfile, blocks_table, people_table, properties_table, cpf, cep, cardinal_direction, house_number, additional_data);
            
                    }
                    else if(strncmp(line, "oloc ", 5) == 0){
                            printf("entrei no oloc\n");
                            sscanf(line, "%s %s %s %c %d %s %lf %lf", helper, property_lease_id, cep, &cardinal_direction, &house_number, additional_data, &property_area, &monthly_rent); 
                            insert_string_in_txt(txtfile, helper);
                            oloc(property_leases, property_lease_id, cep, cardinal_direction, house_number, additional_data, property_area, monthly_rent);
                            
                        }
                        else if(strncmp(line, "oloc?", 5) == 0){
                                printf("entrei no oloc?\n");
                                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                insert_string_in_txt(txtfile, helper);
                                oloc_(svgfile, txtfile, blocks_avl, property_leases, x, y, w, h);

                                }
                                else if(strncmp(line, "loc ", 4) == 0){
                                    printf("entrei no loc\n");
                                    sscanf(line, "%s %s %s", helper, property_lease_id, cpf);
                                    insert_string_in_txt(txtfile, helper);
                                    loc(svgfile, txtfile, blocks_table, property_leases, people_table, property_lease_id, cpf);
                    
                                    }
                                    else if(strncmp(line, "loc?", 4) == 0){
                                        sscanf(line, "%s %s", helper, property_lease_id);
                                        insert_string_in_txt(txtfile, helper);
                                        loc_(svgfile, txtfile, blocks_table, property_leases, property_lease_id);
                        
                                        }
                                        else if(strncmp(line, "dloc", 4) == 0){
                                            sscanf(line, "%s %s", helper, property_lease_id);
                                            insert_string_in_txt(txtfile, helper);
                                            dloc(txtfile, blocks_table, property_leases, property_lease_id);
                            
                                            }
                                            else if(strncmp(line, "hom", 3) == 0){
                                                printf("entrei no hom\n");
                                                sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                insert_string_in_txt(txtfile, helper);
                                                hom(svgfile, txtfile, blocks_avl, properties_table, property_leases, people_table, x, y, w, h);
                                
                                                }
                                                else if(strncmp(line, "mul", 3) == 0){
                                                    sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                    insert_string_in_txt(txtfile, helper);
                                                    mul(svgfile, txtfile, blocks_avl, properties_table, property_leases, people_table, x, y, w, h);
                                                    
                                    
                                                    }
                                                    else if(strncmp(line, "dmpt", 4) == 0){
                                                        sscanf(line, "%s %s", helper, sfx);
                                                        insert_string_in_txt(txtfile, helper);
                                        
                                                        }
                                                        else if(strncmp(line, "catac", 5) == 0){
                                                            printf("entrei no catac\n");
                                                            sscanf(line, "%s %lf %lf %lf %lf", helper, &x, &y, &w, &h);
                                                            insert_string_in_txt(txtfile, helper);
                                                            blocks_avl = catac(svgfile, txtfile, blocks_avl, blocks_table, properties_table, property_leases, people_table, x, y, w, h);

                                            
                                                        }
  
        // "Resets" the string
        strcpy(line, "\0");
    }

    insert_blocks_in_svg(svgfile, blocks_avl);

    free(line);
    free(helper);
    fclose(qryfile);
}


