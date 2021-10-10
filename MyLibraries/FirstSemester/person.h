// 
//  person.h
//  
//
//  Created by Denise F. de Rezende on 14/06/21.
//

#ifndef person_h
#define person_h

typedef void* type_person;

// Creates new person with the parameters specified
type_person new_person(double radiation_level, int alive, int active);

// Returns a copy of an existing person
type_person copy_person(type_person person);

// Functions to change information from the person:
void change_person_alive_status(type_person person, double alive);
void change_person_active_status(type_person person, double active);
void change_person_radiation_level(type_person person, double new_radiation_level);

// Functions to get information from the person:
double get_person_radiation_level(type_person person);
int is_person_alive(type_person person);
int is_person_active(type_person person);

// Removes the person, so that it does not exist anymore
void remove_person(type_person person);

// Function to insert extra position for a person
void add_where_person_went(type_person person, double x, double y);
void get_where_person_went(type_person person, double *x, double *y);

#endif /* person_h */