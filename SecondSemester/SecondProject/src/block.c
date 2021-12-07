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

void remove_block(type_block block){
    BLOCK *b = block;
    free(b);
}
