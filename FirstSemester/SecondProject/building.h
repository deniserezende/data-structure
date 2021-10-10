// 
//  building.h
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#ifndef building_h
#define building_h

typedef void* type_building;

// Creates a new_building with the information if it is active
type_building new_building(int active, int people_inside);

// Functions to change building information:
void change_if_building_is_active(type_building building, int active);
void change_amount_of_people_inside_building(type_building building, int new_amount);
void increase_amount_of_people_inside_building(type_building building, int amount);

// Function to checks building information:
int is_building_active(type_building building);
int get_amount_of_people_inside_building(type_building building);

// Removes the building, so that it does not exist anymore
void remove_building(type_building building);

#endif /* building_h */