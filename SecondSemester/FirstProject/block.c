//
//  block.c
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block.h"

typedef struct block{
    char cep[40];
    long formatted_cep;
    long active;
    //double x, y, w, h; // retangulo ponho aqui ou em outro lugar?
}BLOCK;

type_block new_block(char cep[]){
    BLOCK *block = malloc(sizeof(BLOCK));
    sprintf(block->cep, "%s%c", cep, '\0');
    block->formatted_cep = format_cep_from_base36_to_base10(block->cep);
    block->active = 1;
    return(block);
}

long get_block_formatted_cep(type_block block){
    BLOCK *blocky = block;
    return blocky->formatted_cep;
}

char* get_block_cep(type_block block){
    BLOCK *blocky = block;
    return blocky->cep;
}

long compare_blocks_cep(type_block block1, type_block block2){
    BLOCK *blocky1 = block1;
    BLOCK *blocky2 = block2;
    return(strcmp(blocky1->cep, blocky2->cep));
}

// void change_block_active(type_block block, int active){
//     BLOCK *blocky = block;
//     blocky->active = active;
// }

// long is_block_active(type_block block){
//     BLOCK *blocky = block;
//     return blocky->active;
// }


// int is_block_active(type_block block){
//     BLOCK *b = block;
//     return(b->active);
// }

// void change_if_block_is_active(type_block block, int active){
//     BLOCK *b = block;
//     b->active = active;
// }

// int get_amount_of_people_inside_block(type_block block){
//     BLOCK *b = block;
//     return(b->amount_of_people_inside);
// }

// void change_amount_of_people_inside_block(type_block block, int new_amount){
//     BLOCK *b = block;
//     b->amount_of_people_inside = new_amount;
// }

// void increase_amount_of_people_inside_block(type_block block, int amount){
//     BLOCK *b = block;
//     b->amount_of_people_inside = b->amount_of_people_inside + amount;
// }

void remove_block(type_block block){
    BLOCK *b = block;
    free(b);
}
