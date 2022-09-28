#ifndef TXT_H
#define TXT_H

/* This module provides functions for the creation of a txt file.
	To create a txt file you need to: 
	1- start the creation process with the "start_new_txt_file" function.
	2- if you want elements in it, call the function that inserts the element you want.
	3- end the creation process with the "end_svg_file" function.

	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

typedef void *type_txt;

// Pre-conditions: None
/* Post-conditions: Creates a new file in the directory specified with the filename specified
(How to specify the directory and filname: path/filename.svg = fullpath) 
if a file with that name already exists in that directory, that file is overwritten
if the file can't be created because the path is incomplete or incorrect, returns NULL. */ 
type_txt start_new_txt_file(char *fullpath);
 
// Pre-condition: The txt file with that fullpath has to exist.
// Post-condition: The existing file was opened to append text.
type_txt open_a_pre_existing_txt_file(char *fullpath);

// Pre-condition: The txt file has to have been opened or created (started).
// Post-condition: A string has to have been inserted in the txt file.
void insert_string_in_txt(type_txt file, char *string);

// Pre-condition: The svg file has to have been opened.
// Post-condition: The svg file is now closed. 
// The effect of any other operation called in the closed file is unpredictable. 
void end_txt_file(type_txt file);

#endif


