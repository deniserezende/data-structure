//
//  path.h
//  
//
//  Created by Denise F. de Rezende on 12/03/21.
//

#include "path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_last_slash(char *filename){
	int i, length;
	length = strlen(filename);
	i = length-1;
	// Looking for the last slash
	while(strncmp(&filename[i], "/", 1) != 0){
		i--;
	}
	return(i);
}

int find_last_dot(char *filename){
	int i, length;
	length = strlen(filename);
	i = length - 1;
	// Looking for the last dot
	while(strncmp(&filename[i], ".", 1) != 0){
		i--;
	}
	return(i);
}

char *get_path(char *fullpath){
	char *path;
	int lastslash;
	lastslash = find_last_slash(fullpath);
	path = malloc(sizeof(char) * (lastslash + 1));
	strncpy(path, fullpath, lastslash);
	path[lastslash] = '\0';
	return (path);
}

char *get_filename(char *fullpath){
	char *filename;
	int lastslash, length;
	lastslash = find_last_slash(fullpath);
	length = strlen(fullpath);
	filename = malloc(sizeof(char) * (length - lastslash));
	strncpy(filename, &fullpath[lastslash+1], length-lastslash);
	filename[length-lastslash-1] = '\0';
	return(filename);
}

char *get_filename_without_suffix(char *filename){
	char *name;
	int dot;
	dot = find_last_dot(filename);
	name = malloc(sizeof(char) * dot+1);
	strncpy(name, filename, dot);
	name[dot] = '\0';
	return(name);
}

char *get_suffix(char *filename){
	int length, dot;
	char *suffix;
	length = strlen(filename);
	dot = find_last_dot(filename);
	suffix = malloc(sizeof(char) * (length - dot)); 
	strncpy(suffix, &filename[dot+1], length);
	suffix[length-dot-1] = '\0';
	return(suffix);
}

char* concat_name_suffix(char *name, char *suffix){
	char *filename;
	if(has_dot(suffix)){
		filename = malloc((strlen(name) + strlen(suffix) + 2) * sizeof(char));  //+1 for the null character '\0'
		sprintf(filename, "%s%s%c", name, suffix, '\0');
	}
	else{
		filename = malloc((strlen(name) + strlen(suffix) + 3) * sizeof(char)); //+2 for the dot and the null character '\0'
		sprintf(filename, "%s%s%s%c", name, ".", suffix, '\0');
	}

	return(filename);
}

int has_dot(char *suffix){
	if(strncmp(&suffix[0], ".", 1) == 0){
		return 1;
	}
	return 0;
}

int path_has_slash(char *path){
	int length;
	length = strlen(path);
	if(strncmp(&path[length-1], "/", 1) == 0){
		return 1;
	}
	return 0;
}

int filename_has_slash(char *filename){
	if(strncmp(&filename[0], "/", 1) == 0){
		return 1;
	}
	return 0;
}

char *concat_path_filename(char *path, char *filename){
	char *fullpath;
	if(path_has_slash(path) && filename_has_slash(filename)){
		path[strlen(path)-1] = '\0';
		fullpath = malloc(sizeof(char) * (strlen(path) + strlen(filename) +2)); //+1 for the null character '\0'
		sprintf(fullpath, "%s%s%c", path, filename, '\0');
	}
	else if(!path_has_slash(path) && !filename_has_slash(filename)){
		fullpath = malloc(sizeof(char) * (strlen(path) + strlen(filename) +3)); //+2 for the slash and the null character '\0'
		sprintf(fullpath, "%s%s%s%c", path, "/", filename, '\0');
	}
	else{ //if only one of them has the '/'
		fullpath = malloc(sizeof(char) * (strlen(path) + strlen(filename) +2)); //+1 for the null character '\0'
		sprintf(fullpath, "%s%s%c", path, filename, '\0');
	}
	return(fullpath);
}




