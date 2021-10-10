//
//  commandline.c
//  
//
//  Created by Denise F. de Rezende on 04/06/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commandline.h"

void commandline(int argc, char *argv[], char **input_path, char **geo_filename, char **qry_filename, char **output_path){
    int i = 1; // Motive to start 'i' in 1: first file, with the index equal to zero, is the name of the compiling file aka this file!
    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++; // After the "-e" comes the input path
            *input_path = malloc((strlen(argv[i])+1) *sizeof(char));
            sprintf(*input_path, "%s", argv[i]); // Copies the value of argv
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++; // After the "-f" comes the geo filename
            *geo_filename = malloc((strlen(argv[i])+1) *sizeof(char));
            sprintf(*geo_filename, "%s", argv[i]); // Copies the value of argv
            }
            else if(strcmp("-q", argv[i]) == 0){
                    i++; // After the "-q" comes the qry filename
                    *qry_filename = malloc((strlen(argv[i])+1) *sizeof(char));
                    sprintf(*qry_filename, "%s", argv[i]); // Copies the value of argv
                }
                else if(strcmp("-o", argv[i]) == 0){
                        i++; // After the "-o" comes the output path
                        *output_path = malloc((strlen(argv[i])+1) *sizeof(char));
                        sprintf(*output_path, "%s", argv[i]); // Copies the value of argv
                    }
                    else{
                        i++;
                    }
                    i++;
    }
}