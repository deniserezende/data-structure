//
//  graphviz_draw.h
//  
//
//  Created by Denise F. de Rezende on 03/09/21.
//

#ifndef graphviz_draw_h
#define graphviz_draw_h


FILE *begin_design(const char *output_filename);

void end_design(FILE *output_file);

void add_tree_element(char* parent, char* child_left, char* child_right, FILE *output_file);

#endif