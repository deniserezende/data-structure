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
    int alive;
    int active;
    double radiation_level;
    double rantox, rantoy;
}PERSON;


type_person new_person(double radiation_level, int alive, int active){
    PERSON *person = malloc(sizeof(PERSON));
    person->radiation_level = radiation_level;
    person->alive = alive;
    person->active = active;
    return(person);
}

type_person copy_person(type_person person){
    PERSON *p = person;
    PERSON *cpyperson = malloc(sizeof(PERSON));
    cpyperson->radiation_level = p->radiation_level;
    cpyperson->alive = p->alive;
    cpyperson->active = p->active;
    return(cpyperson);
}

void change_person_radiation_level(type_person person, double new_radiation_level){
    PERSON *p = person;
    p->radiation_level = new_radiation_level;
}

double get_person_radiation_level(type_person person){
    PERSON *p = person;
    return(p->radiation_level);
}

void change_person_alive_status(type_person person, double alive){
    PERSON *p = person;
    p->alive = alive;
}

int is_person_alive(type_person person){
    PERSON *p = person;
    return(p->alive);
}

void change_person_active_status(type_person person, double active){
    PERSON *p = person;
    p->active = active;
}

int is_person_active(type_person person){
    PERSON *p = person;
    return(p->active);
}


void add_where_person_went(type_person person, double x, double y){
    PERSON *p = person;
    p->rantox = x;
    p->rantoy = y;
}

void get_where_person_went(type_person person, double *x, double *y){
    PERSON *p = person;
    *x = p->rantox;
    *y = p->rantoy;
}

void remove_person(type_person person){
    PERSON *p = person;
    free(p);
}

