// 
//  property.h
//  
//
//  Created by Denise F. de Rezende on 12/09/21.
//

#ifndef property_h
#define property_h

#include "string_editing.h"

typedef void* type_property;
typedef void* type_person_copy;


type_property new_property(char cep[], char cardinal_direction, int house_number, char add_address_data[]);

int get_property_house_number(type_property property);

void add_property_area(type_property property, double area);

double get_property_area(type_property property);

void add_property_monthly_rent(type_property property, double monthly_rent);

double get_property_monthly_rent(type_property property);

void add_lease_id_to_property(type_property property, char lease_id[]);

long get_property_lease_key(type_property);

char* get_property_lease_id(type_property property);

void add_property_owner(type_property property, type_person_copy owner);

type_person_copy get_property_owner(type_property property);

void change_property_rent_status(type_property property, int is_for_rent);

int get_property_rent_status(type_property property);

int add_property_tenant(type_property property, type_person_copy tenant);

type_person_copy get_property_tenant(type_property property);

int get_property_number(type_property property);

char* get_property_cep(type_property property);

long get_property_cep_key(type_property property);

char get_property_cardinal_direction(type_property property);

char* get_property_additional_address_data(type_property property);

void remove_property(type_property property);

#endif /* property_h */