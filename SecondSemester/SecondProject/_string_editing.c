// 
//  string_editing.c
//  
//
//  Created by Denise F. de Rezende on 15/09/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "_string_editing.h"

char* remove_all_occurrences_of_char(char* str, char c){
    char *result = malloc(sizeof(char) * strlen(str) + 2);
    sprintf(result, "%s%c", str, '\0');
    char *pr = result, *pw = result;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';

    return result;
}

long convert_base36_to_base10(char *base36){
    char tmp;
    char dictionary[36][2] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    long result = 0;
    int index = 1;

    for(int i = 0; i <= strlen(base36); i++){
        tmp = toupper(base36[i]);
        for(int j = 0; j < 36; j++){
            if(strncmp(&dictionary[j][0], &tmp, 1) == 0){
                if(strlen(base36) < index) return -1;
                result += j * pow(36, strlen(base36) - index);
                index++;
                break;
            }
        }
    }

    return result;
}


char* format_cep(char cep[]){
    char* cep_without_hyphen = remove_all_occurrences_of_char(cep, '-');
    char* cep_without_special_characters = remove_all_occurrences_of_char(cep_without_hyphen, '.');

    return cep_without_special_characters;
}

long format_cep_from_base36_to_base10(char cep[]){
    char* cep_without_hyphen = remove_all_occurrences_of_char(cep, '-');
    char* cep_without_special_characters = remove_all_occurrences_of_char(cep_without_hyphen, '.');

    long result = convert_base36_to_base10(cep_without_special_characters);
    free(cep_without_hyphen);
    free(cep_without_special_characters);

    return result;
}

long format_cpf(char cpf[]){
    char* cpf_without_hyphen = remove_all_occurrences_of_char(cpf, '-');
    char* cpf_without_special_characters = remove_all_occurrences_of_char(cpf_without_hyphen, '.');

    long result = atol(cpf_without_special_characters);
    free(cpf_without_hyphen);
    free(cpf_without_special_characters);
    return result;
}