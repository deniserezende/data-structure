// 
//  block.h
//  
//
//  Created by Denise F. de Rezende on 10/06/21.
//

#ifndef block_h
#define block_h

#include "_string_editing.h"

typedef void* type_block;

type_block new_block(char cep[]);

long get_block_formatted_cep(type_block block);

char* get_block_cep(type_block block);

long compare_blocks_cep(type_block block1, type_block block2);

void remove_block(type_block block);

#endif /* block_h */

