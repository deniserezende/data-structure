#ifndef PATH_H  // file guard is a particular construct used to avoid the problem of double inclusion when dealing with the include directive. 
#define PATH_H	

/* This module provides functions for dealing with directory paths and filenames.
    Note that: This is a module that works in Linux environment and not in windows.

	Note that: Every function has it's specifications if ignored the result is unpredictable!
*/

// Given a file's full path, returns an integer of where the lash slash is located
int find_last_slash(char *filename);

// Given a file's name, returns an integer of where the lash dot is located
int find_last_dot(char *filename);

// Given a file's full path, returns the pathway without the file's name and without the forward slash
char *get_path(char *fullpath);

// Given a file's full path, returns the file's name with it's suffix 
char *get_filename(char *fullpath);

// Given a file's name, returns the file's name without it's suffix 
char *get_filename_without_suffix(char *filename);

// Given the name of the file with suffix, returns the suffix
char *get_suffix(char *filename);

// Concatenates the name without suffixx with the suffix
char* concat_name_suffix(char *name, char *suffix);

// Verifies if the suffix starts with a dot and returns a boolean
int has_dot(char *suffix);

// Verifies if the pathway ends with a slash and returns a boolean
int path_has_slash(char *path);

// Concatenates the fullpath without a filename with the filename and suffix
char *concat_path_filename(char *path, char *filename);

#endif
