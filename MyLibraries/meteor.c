//
//  meteor.c
//  
//
//  Created by Denise F. de Rezende on 14/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meteor.h"

typedef struct meteor{
    double x, y;
    double radiation_level;
}METEOR;


type_meteor new_meteor(double x, double y, double radiation_level){
    METEOR *meteor = malloc(sizeof(METEOR));
    meteor->x = x;
    meteor->y = y;
    meteor->radiation_level = radiation_level;
    return(meteor);
}

void change_meteor_radiation_level(type_meteor meteor, double new_radiation_level){
    METEOR *m = meteor;
    m->radiation_level = new_radiation_level;
}

double get_meteor_radiation_level(type_meteor meteor){
    METEOR *m = meteor;
    return(m->radiation_level);
}


void change_meteor_x(type_meteor meteor, double new_x){
    METEOR *m = meteor;
    m->x = new_x;
}

double get_meteor_x(type_meteor meteor){
    METEOR *m = meteor;
    return(m->x);
}

void change_meteor_y(type_meteor meteor, double new_y){
    METEOR *m = meteor;
    m->y = new_y;
}

double get_meteor_y(type_meteor meteor){
    METEOR *m = meteor;
    return(m->y);
}

void remove_meteor(type_meteor meteor){
    METEOR *m = meteor;
    free(m);
}

