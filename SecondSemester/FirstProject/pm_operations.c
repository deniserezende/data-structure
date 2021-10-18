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

void get_pm_input(char *filename, type_hashtable people_table, type_hashtable properties_table){
    FILE *pmfile = fopen(filename, "r");
    if(pmfile == NULL){
        return;
    }

    char *line = malloc(80 * sizeof(char));
    char *helper = malloc(3 *sizeof(char));
    char *cpf = malloc(40 * sizeof(char));
    char *first_name = malloc(40 * sizeof(char));
    char *last_name = malloc(40 * sizeof(char));
    char *birthday = malloc(11 * sizeof(char));
    char gender;

    char *cep = malloc(40 * sizeof(char));
    char *add_address_data = malloc(40 * sizeof(char));
    char cardinal_direction;
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

    free(line);
    free(helper);
    free(cpf);
    free(first_name);
    free(last_name);
    free(birthday);
    free(cep);
    //free(add_address_data);
    fclose(pmfile);
}