//
//  SVG.c
//  
//
//  Created by Denise F. de Rezende on 12/03/21.
//

#include "TXT.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct txt_structure {
	FILE *ftxt;
}STRUCTTXT;


type_txt start_new_txt_file(char *fullpath){
	FILE *f = fopen(fullpath,"w"); //open to write
	if (f == NULL){
		return NULL;
	}
    STRUCTTXT *txt_cell = malloc(sizeof(STRUCTTXT));
    txt_cell->ftxt = f;
    return txt_cell; 
}

type_txt open_a_pre_existing_txt_file(char *fullpath){
	FILE *f = fopen(fullpath,"a"); //open to append
	if (f == NULL){
		return NULL;
	}
    STRUCTTXT *txt_cell = malloc(sizeof(STRUCTTXT));
    txt_cell->ftxt = f;
    return txt_cell; 
}

void insert_string_in_txt(type_txt file, char *string){
	STRUCTTXT *f = file; 
	
    fprintf(f->ftxt,"%s\n", string);
}

void insert_string_without_skipping_line_in_txt(type_txt file, char *string){
	STRUCTTXT *f = file; 
	
    fprintf(f->ftxt,"%s", string);
}

void end_txt_file(type_txt file){
   	STRUCTTXT *f = file;
    insert_string_in_txt(file, "\0");
	fclose(f->ftxt);
	free(f); 
}

 