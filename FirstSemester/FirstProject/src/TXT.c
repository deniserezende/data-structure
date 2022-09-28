#include "TXT.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct txt_structure {
	FILE *ftxt;
}STRUCTTXT;

// Pre-conditions: None
/* Post-conditions: Creates a new file in the directory specified with the filename specified
(How to specify the directory and filname: path/filename.svg = fullpath) 
if a file with that name already exists in that directory, that file is overwritten
if the file can't be created because the path is incomplete or incorrect, returns NULL. */ 
type_txt start_new_txt_file(char *fullpath){
	FILE *f = fopen(fullpath,"w"); //open to write
	if (f == NULL){
		return NULL;
	}
    STRUCTTXT *txt_cell = malloc(sizeof(STRUCTTXT));
    txt_cell->ftxt = f;
    return txt_cell; 
}

// Pre-condition: The txt file with that fullpath has to exist.
// Post-condition: The existing file was opened to append text.
type_txt open_a_pre_existing_txt_file(char *fullpath){
	FILE *f = fopen(fullpath,"a"); //open to append
	if (f == NULL){
		return NULL;
	}
    STRUCTTXT *txt_cell = malloc(sizeof(STRUCTTXT));
    txt_cell->ftxt = f;
    return txt_cell; 
}

// Pre-condition: The txt file has to have been opened or created (started).
// Post-condition: A string has to have been inserted in the txt file.
void insert_string_in_txt(type_txt file, char *string){
	STRUCTTXT *f = file; 
	
    fprintf(f->ftxt,"%s\n", string);
}

// Pre-condition: The svg file has to have been opened.
// Post-condition: The svg file is now closed. 
// The effect of any other operation called in the closed file is unpredictable. 
void end_txt_file(type_txt file){
   	STRUCTTXT *f = file;
    insert_string_in_txt(file, "\0");
	fclose(f->ftxt);
	free(f); 
}

 