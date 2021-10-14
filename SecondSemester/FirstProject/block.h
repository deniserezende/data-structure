// 
//  block.h
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#ifndef block_h
#define block_h

#include "string_editing.h"


typedef void* type_block;

// Creates a new_block with the information if it is active
type_block new_block(char cep[]);

long get_block_formatted_cep(type_block block);

char* get_block_cep(type_block block);

long compare_blocks_cep(type_block block1, type_block block2);

// void change_block_active(type_block block, int active);
// long is_block_active(type_block block);

// // Functions to change block information:
// void change_if_block_is_active(type_block block, int active);
// void change_amount_of_people_inside_block(type_block block, int new_amount);
// void increase_amount_of_people_inside_block(type_block block, int amount);

// // Function to checks block information:
// int is_block_active(type_block block);
// int get_amount_of_people_inside_block(type_block block);

// Removes the block, so that it does not exist anymore
void remove_block(type_block block);

#endif /* block_h */

