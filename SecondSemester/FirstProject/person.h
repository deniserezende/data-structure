// 
//  person.h
//  
//
//  Created by Denise F. de Rezende on 14/06/21.
//

#ifndef person_h
#define person_h

#include "string_editing.h"

typedef void* type_person;
typedef void* type_property_copy;

type_person new_person(char cpf[], char first_name[], char last_name[], char gender, char birthday[]);

char* get_person_full_name(type_person person);

char* get_person_first_name(type_person person);

char* get_person_birthday(type_person person);

char* get_person_cpf(type_person person);

long compare_peoples_cpf(type_person person1, type_person person2);

long get_person_formatted_cpf(type_person person);

long does_person_own_properties(type_person person);

long does_person_rents_properties(type_person person);

// if you removed the last property from person than you have to set owned properties to person again
// you can check this using the function long does_person_own_properties(type_person person);
type_property_copy remove_owned_property_from_person(type_person person, int index);

type_property_copy remove_rented_property_from_person(type_person person, int index);

void set_owned_properties_to_person(type_person person, int amount);

void add_persons_owned_property(type_person person, type_property_copy property);

void set_properties_leases_to_person(type_person person, int amount);

void add_persons_property_lease(type_person person, type_property_copy property);

type_property_copy* get_person_properties_leases(type_person person);

int get_amount_of_owned_properties(type_person person);
int get_amount_of_rented_properties(type_person person);

// index starts in zero!
type_property_copy get_person_property_lease(type_person person, int index);
type_property_copy get_person_owned_property(type_person person, int index);

char get_person_gender(type_person person);

void remove_person(type_person person);

#endif /* person_h */