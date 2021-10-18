//
//  property.c
//  
//
//  Created by Denise F. de Rezende on 12/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "property.h"

typedef struct property{
    char cep[40];
    char cardinal_direction;
    char add_address_data[40];
    int house_number;

    long formatted_cep;
    double area;
    double monthly_rent;

    int is_for_rent;
    char lease_id[40];
    long formatted_lease;
    type_person_copy owner;
    type_person_copy tenant;
}PROPERTY;


type_property new_property(char cep[], char cardinal_direction, int house_number, char add_address_data[]){
    PROPERTY *property = malloc(sizeof(PROPERTY));

    sprintf(property->cep, "%s%c", cep, '\0');
    property->formatted_cep = format_cep_from_base36_to_base10(property->cep);

    property->cardinal_direction = cardinal_direction;
    sprintf(property->add_address_data, "%s%c", add_address_data, '\0');
    property->house_number = house_number;
    property->is_for_rent = 0;
    property->owner = NULL;
    property->tenant = NULL;

    return(property);
}

int get_property_house_number(type_property property){
    PROPERTY *prop = property;
    return prop->house_number;
}

void add_property_area(type_property property, double area){
    PROPERTY *prop = property;
    prop->area = area;
}

double get_property_area(type_property property){
    PROPERTY *prop = property;
    return(prop->area);
}

long compare_properties_cep(type_property property1, type_property property2){
    PROPERTY *prop1 = property1;
    PROPERTY *prop2 = property2;
    return(strcmp(prop1->cep, prop2->cep));
}

long compare_properties_leases_id(type_property property1, type_property property2){
    PROPERTY *prop1 = property1;
    PROPERTY *prop2 = property2;
    return(strcmp(prop1->lease_id, prop2->lease_id));
}


void add_property_monthly_rent(type_property property, double monthly_rent){
    PROPERTY *prop = property;
    prop->monthly_rent = monthly_rent;
}

double get_property_monthly_rent(type_property property){
    PROPERTY *prop = property;
    return(prop->monthly_rent);
}

void add_lease_id_to_property(type_property property, char lease_id[]){
    PROPERTY *prop = property;
    sprintf(prop->lease_id, "%s%c", lease_id, '\0');
    prop->formatted_lease = format_cep_from_base36_to_base10(prop->lease_id);
}

long get_property_lease_key(type_property property){
    PROPERTY *prop = property;
    return prop->formatted_lease;
}

char* get_property_lease_id(type_property property){
    PROPERTY *prop = property;
    return prop->lease_id;
}

void add_property_owner(type_property property, type_person_copy owner){
    PROPERTY *prop = property;
    prop->owner = owner;
}

type_person_copy get_property_owner(type_property property){
    PROPERTY *prop = property;
    return prop->owner;
}

int get_property_rent_status(type_property property){
    PROPERTY *prop = property;
    return prop->is_for_rent;
}

void change_property_rent_status(type_property property, int is_for_rent){
    PROPERTY *prop = property;
    prop->is_for_rent = is_for_rent;
}

char get_property_cardinal_direction(type_property property){
    PROPERTY *prop = property;
    return prop->cardinal_direction;
}

int add_property_tenant(type_property property, type_person_copy tenant){
    PROPERTY *prop = property;
    if(prop->is_for_rent == 0) return 0;
    prop->tenant = tenant;
    return 1;
}

type_person_copy get_property_tenant(type_property property){
    PROPERTY *prop = property;
    return prop->tenant;
}

int get_property_number(type_property property){
    PROPERTY *prop = property;
    return prop->house_number;
}

char* get_property_cep(type_property property){
    PROPERTY *prop = property;
    return prop->cep;
}

long get_property_cep_key(type_property property){
    PROPERTY *prop = property;
    return prop->formatted_cep;
}

char* get_property_additional_address_data(type_property property){
    PROPERTY *prop = property;
    return prop->add_address_data;
}




void remove_property(type_property property){
    PROPERTY *p = property;
    free(p);
}


// typedef struct base36_dictionary{
//     char const A=10, B=11, C=12, D=13, E=14, F=15, G=16, H=17, I=18, J=19, K=20;
//     char const L=21, M=22, N=23, O=24, P=25, Q=26, R=27, S=28, T=29, U=30, V=31, W=32, X=33, Y=34, Z=35; 
//     char vector_base36[1][36] = {'0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35'}
//     //int vector_base36[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35}

// }DICTIONARY;
