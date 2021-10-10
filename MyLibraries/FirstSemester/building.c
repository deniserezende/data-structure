//
//  building.c
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "building.h"

typedef struct building{
    int active;
    int amount_of_people_inside;
}BUILDING;

type_building new_building(int active, int people_inside){
    BUILDING *building = malloc(sizeof(BUILDING));
    building->active = active;
    building->amount_of_people_inside = people_inside;
    return(building);
}

int is_building_active(type_building building){
    BUILDING *b = building;
    return(b->active);
}

void change_if_building_is_active(type_building building, int active){
    BUILDING *b = building;
    b->active = active;
}

int get_amount_of_people_inside_building(type_building building){
    BUILDING *b = building;
    return(b->amount_of_people_inside);
}

void change_amount_of_people_inside_building(type_building building, int new_amount){
    BUILDING *b = building;
    b->amount_of_people_inside = new_amount;
}

void increase_amount_of_people_inside_building(type_building building, int amount){
    BUILDING *b = building;
    b->amount_of_people_inside = b->amount_of_people_inside + amount;
}

void remove_building(type_building building){
    BUILDING *b = building;
    free(b);
}
