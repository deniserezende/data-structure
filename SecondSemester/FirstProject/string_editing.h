// 
//  string_editing.h
//  
//
//  Created by Denise F. de Rezende on 15/09/21.
//

#ifndef string_editing_h
#define string_editing_h

long convert_base36_to_base10(char* base36);
char* remove_all_occurrences_of_char(char* str, char c);
char* format_cep(char cep[]);
long format_cep_from_base36_to_base10(char cep[]);
long format_cpf(char cpf[]);

#endif /* string_editing_h */