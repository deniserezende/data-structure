// 
//  meteor.h
//  
//
//  Created by Denise F. de Rezende on 14/06/21.
//

#ifndef meteor_h
#define meteor_h

typedef void* type_meteor;

// Creates new meteor with the parameters specified
type_meteor new_meteor(double x, double y, double radiation_level);

// Functions to change information from the meteor:
void change_meteor_radiation_level(type_meteor meteor, double new_radiation_level);
void change_meteor_x(type_meteor meteor, double new_x);
void change_meteor_y(type_meteor meteor, double new_y);

// Functions to get information from the meteor:
double get_meteor_radiation_level(type_meteor meteor);
double get_meteor_x(type_meteor meteor);
double get_meteor_y(type_meteor meteor);

// Removes the meteor, so that it does not exist anymore
void remove_meteor(type_meteor meteor);

#endif /* meteor_h */