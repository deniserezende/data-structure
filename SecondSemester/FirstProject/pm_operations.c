//
//  pm_operations.c
//  
//
//  Created by Denise F. de Rezende on 12/09/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pm_operations.h"

void print_id(type_hashitem item){
    printf("cpf: %s\n", get_person_cpf(item));
}

void get_pm_input(char *filename, type_hashtable people_table, type_hashtable properties_table){
    FILE *pmfile = fopen(filename, "r");
    if(pmfile == NULL){
        return;
    }

    char *line = malloc(80 * sizeof(char));
    char *helper = malloc(3 *sizeof(char));
    char cpf[40], first_name[40], last_name[40], birthday[10]; // 10 ou 11 AQUIDE
    char gender;
    char cep[40], cardinal_direction, add_address_data[40];
    int house_number;

    type_person person;
    
    // Creating a pointer to the function
    long(*get_cpf_ptr)(type_person);
    get_cpf_ptr = get_person_formatted_cpf;

    // Creating a pointer to the function
    long(*get_cep_ptr)(type_property);
    get_cep_ptr = get_property_cep_key;

    // Creating a pointer to the function
    long(*check_person_ptr)(type_property);
    check_person_ptr = verify_person_found;

    void(*debug)(type_property);
    debug = print_id;


    while(!feof(pmfile)){
        fscanf(pmfile, "\n%[^\n]s\n", line);
        
        if(strncmp(line, "p", 1) == 0){
            sscanf(line, "%s %s %s %s %c %s", helper, cpf, first_name, last_name, &gender, birthday); // &gender?
            person = new_person(cpf, first_name, last_name, gender, birthday);
            insert_item_in_hash_table(people_table, person, get_person_formatted_cpf(person), (void*)get_cpf_ptr, (void*)compare_peoples_cpf);
        }

        else if(strncmp(line, "m", 1) == 0){
                sscanf(line, "%s %s %s %s %d %s", helper, cpf, cep, &cardinal_direction, &house_number, add_address_data); // &gender?
                type_property new_property_ = new_property(cep, cardinal_direction, house_number, add_address_data);

                long cpf_formatted = format_cpf(cpf);
                set_id(cpf);
                person = lookup_item_in_hash_table(people_table, cpf_formatted, (void*)get_cpf_ptr, (void*)check_person_ptr);
                set_owned_properties_to_person(person, 1);
                add_persons_owned_property(person, new_property_);

                add_property_owner(new_property_, person);
                insert_item_in_hash_table(properties_table, new_property_,  get_property_cep_key(new_property_), (void*)get_cep_ptr, (void*)compare_properties_cep);
            }
            else break;
        // "Resets" the string
        strcpy(line, "\0");
    }
    //print_hash_table(people_table, (void*)debug);

    free(line);
    free(helper);
    fclose(pmfile);
}