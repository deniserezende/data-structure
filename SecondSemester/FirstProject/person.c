//
//  person.c
//  
//
//  Created by Denise F. de Rezende on 14/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

typedef struct person{
    char cpf[40];
    char first_name[40];
    char last_name[40];
    char gender;
    char birthday[12];

    long formatted_cpf;

    int has_property_leases;
    int amount_of_properties_leases;
    type_property_copy *properties_leases;

    int own_properties;
    int amount_of_owned_properties;
    type_property_copy *properties_owned;
    // char cep[40], cardinal_direction, add_address_data[40];
    // int house_number;
}PERSON;


type_person new_person(char cpf[], char first_name[], char last_name[], char gender, char birthday[]){
    PERSON *person = malloc(sizeof(PERSON));

    sprintf(person->cpf, "%s%c", cpf, '\0');
    person->formatted_cpf = format_cpf(person->cpf);
    sprintf(person->first_name, "%s%c", first_name, '\0');
    sprintf(person->last_name, "%s%c", last_name, '\0');
    person->gender = gender; 
    sprintf(person->birthday, "%s%c", birthday, '\0');

    person->has_property_leases = 0;
    person->own_properties = 0;
    person->amount_of_properties_leases = 0;
    person->amount_of_owned_properties = 0;
    return(person);
}


char* get_person_birthday(type_person person){
    PERSON *p = person;
    return(p->birthday);
}

char* get_person_full_name(type_person person){
    PERSON *p = person;
    char* full_name = malloc(sizeof(char) * (strlen(p->first_name) + strlen(p->last_name) + 3));
    sprintf(full_name, "%s %s%c", p->first_name, p->last_name, '\0');
    return(full_name);
}

char* get_person_first_name(type_person person){
    PERSON *p = person;
    return(p->first_name);
}

char* get_person_cpf(type_person person){
    PERSON *p = person;
    return(p->cpf);
}

long get_person_formatted_cpf(type_person person){
    PERSON *p = person;
    return(p->formatted_cpf);
}

long does_person_own_properties(type_person person){
    PERSON *p = person;
    return p->own_properties;
}

long does_person_rents_properties(type_person person){
    PERSON *p = person;
    return p->has_property_leases;
}

// if you removed the last property from person than you have to set owned properties to person again
// you can check this using the function long does_person_own_properties(type_person person);
type_property_copy remove_owned_property_from_person(type_person person, int index){
    PERSON *p = person;
    if(index > p->amount_of_owned_properties) return NULL;
    type_property_copy old_property = p->properties_owned[index];
    p->properties_owned[index] = NULL;
    
    for(int i = 0; i < p->amount_of_owned_properties; i++){
        if(p->properties_owned[i] != NULL){
            return old_property;
        }
    }
    p->own_properties = 0;
    p->amount_of_owned_properties = 0;
    return old_property;
}

type_property_copy remove_rented_property_from_person(type_person person, int index){
    PERSON *p = person;
    if(index > p->amount_of_properties_leases) return NULL;
    type_property_copy old_property = p->properties_leases[index];
    p->properties_leases[index] = NULL;
    
    for(int i = 0; i < p->amount_of_owned_properties; i++){
        if(p->properties_leases[i] != NULL){
            return old_property;
        }
    }
    p->own_properties = 0;
    free(p->properties_leases);
    return old_property;
}

long compare_peoples_cpf(type_person person1, type_person person2){
    PERSON *p1 = person1;
    PERSON *p2 = person2;
    return(strcmp(p1->cpf, p2->cpf));
}

void set_owned_properties_to_person(type_person person, int amount){
    PERSON *p = person;

    p->own_properties = 1;
    p->amount_of_owned_properties = amount;
    p->properties_owned = malloc(sizeof(type_property_copy) * amount);

    for(int i = 0; i < amount; i++){
        p->properties_owned[i] = NULL;
    }
}

void add_persons_owned_property(type_person person, type_property_copy property){
    PERSON *p = person;

    for(int i = 0; i < p->amount_of_owned_properties; i++){
        if(p->properties_owned[i] == NULL){
            p->properties_owned[i] = property;
            break; 
        }
    }
    
}

int get_amount_of_owned_properties(type_person person){
    PERSON *p = person;
    return p->amount_of_owned_properties;
}

int get_amount_of_rented_properties(type_person person){
    PERSON *p = person;
    return p->amount_of_properties_leases;
}

void set_properties_leases_to_person(type_person person, int amount){
    PERSON *p = person;

    p->has_property_leases = 1;
    p->amount_of_properties_leases = amount;
    p->properties_leases = malloc(sizeof(type_property_copy) * amount);

    for(int i = 0; i < amount; i++){
        p->properties_leases[i] = NULL;
    }
}

void add_persons_property_lease(type_person person, type_property_copy property){
    PERSON *p = person;

    for(int i = 0; i < p->amount_of_properties_leases; i++){
        if(p->properties_leases[i] == NULL){
            p->properties_leases[i] = property;
            break; 
        }
    }
    
}

type_property_copy* get_person_properties_leases(type_person person){
    PERSON *p = person;
    return p->properties_leases;
}

type_property_copy get_person_property_lease(type_person person, int index){
    PERSON *p = person;
    if(index > p->amount_of_properties_leases) return NULL;
    return p->properties_leases[index];
}


type_property_copy get_person_owned_property(type_person person, int index){
    PERSON *p = person;
    if(index > p->amount_of_owned_properties) return NULL;
    return p->properties_owned[index];
}

char get_person_gender(type_person person){
    PERSON *p = person;
    return p->gender;
}

void remove_person(type_person person){
    PERSON *p = person;
    free(p);
}