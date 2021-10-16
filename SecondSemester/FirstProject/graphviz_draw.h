//
//  graphviz_draw.h
//  
//
//  Created by Denise F. de Rezende on 03/09/21.
//

#ifndef graphviz_draw_h
#define graphviz_draw_h

#include "list.h"

typedef void* type_dot;
typedef void* type_gdptrf_onelist(type_list);

type_dot begin_design(const char *filename);


void end_design(type_dot file);

void appear_node_in_tree_design(type_dot file);
void hide_node_in_tree_design(type_dot file);

void add_root_in_tree_design(char* root, type_dot file);

void add_tree_element(char* parent, char* child_left, char* child_right, type_dot file);

void add_child_in_tree_design(char* child, type_dot file);
void add_parent_in_tree_design(char* parent, type_dot file);
void add_empty_child_in_tree_design(type_dot file);

void insert_blocks_rects_parent_list_of_not_null_child(type_dot file, type_list parent, type_gdptrf_onelist get_info);
void insert_blocks_rects_parent_list_of_null_child(type_dot file, type_list parent, type_gdptrf_onelist get_info);
void insert_blocks_rects_child_list(type_dot file, type_list child, type_gdptrf_onelist get_info);

void close_child(type_dot file);

#endif