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

void appear_node_in_tree_design(FILE *output_file);
void hide_node_in_tree_design(FILE *output_file);

void add_root_in_tree_design(char* root, FILE *output_file);

void add_tree_element(char* parent, char* child_left, char* child_right, FILE *output_file);

void add_child_in_tree_design(char* child, FILE *output_file);
void add_parent_in_tree_design(char* parent, FILE *output_file);
void add_empty_child_in_tree_design(FILE *output_file);

void close_child(FILE *output_file);

#endif