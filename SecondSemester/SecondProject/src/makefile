LINK_TARGET = t2

OBJECTS = _auxiliary_functions.o _geometry_operations.o _string_editing.o ascending_priority_queue.o block.o commandline.o descending_priority_queue.o dijkstras_algorithm.o disjoint_sets.o edge.o geo_operations.o graph.o hash_table.o kruskals_algorithm.o list_dynamic.o main.o mM_avl_tree_wlist.o output_svg.o path.o property.o qry_catac.o qry_cx.o qry_o_.o qry_operations.o qry_p_.o qry_rv.o rectangle.o strongly_connected_components_algorithm.o SVG.o TXT.o vertex.o via_operations.o

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
_auxiliary_functions.o : _auxiliary_functions.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h TXT.h vertex.h edge.h property.h
_geometry_operations.o : _geometry_operations.h rectangle.h
_string_editing.o : _string_editing.h
ascending_priority_queue.o : ascending_priority_queue.h descending_priority_queue.h
block.o : block.h _string_editing.h
commandline.o : commandline.h
descending_priority_queue.o : descending_priority_queue.h
dijkstras_algorithm.o : dijkstras_algorithm.h graph.h list.h ascending_priority_queue.h
disjoint_sets.o : disjoint_sets.h
edge.o : edge.h
geo_operations.o : geo_operations.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h _auxiliary_functions.h
graph.o : graph.h list.h ascending_priority_queue.h
hash_table.o : hash_table.h list.h
kruskals_algorithm.o : kruskals_algorithm.h graph.h disjoint_sets.h ascending_priority_queue.h
list_dynamic.o : list.h
main.o : commandline.h path.h geo_operations.h via_operations.h graph.h mM_avl_tree_wlist.h hash_table.h output_svg.h qry_operations.h vertex.h edge.h
mM_avl_tree_wlist.o : mM_avl_tree_wlist.h list.h
output_svg.o : output_svg.h SVG.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h graph.h vertex.h edge.h
path.o : path.h
property.o : property.h _string_editing.h
qry_catac.o : qry_catac.h hash_table.h rectangle.h block.h _auxiliary_functions.h SVG.h TXT.h graph.h vertex.h _geometry_operations.h edge.h
qry_cx.o : qry_cx.h graph.h vertex.h edge.h _auxiliary_functions.h SVG.h strongly_connected_components_algorithm.h
qry_o_.o : qry_o_.h property.h SVG.h TXT.h _auxiliary_functions.h hash_table.h _geometry_operations.h
qry_operations.o : qry_operations.h SVG.h TXT.h qry_catac.h qry_p_.h qry_o_.h qry_cx.h qry_rv.h output_svg.h path.h graph.h property.h
qry_p_.o : qry_p_.h hash_table.h rectangle.h block.h _auxiliary_functions.h SVG.h TXT.h graph.h dijkstras_algorithm.h property.h edge.h vertex.h _geometry_operations.h
qry_rv.o : qry_rv.h graph.h vertex.h edge.h rectangle.h _geometry_operations.h kruskals_algorithm.h _auxiliary_functions.h SVG.h
rectangle.o : rectangle.h
strongly_connected_components_algorithm.o : strongly_connected_components_algorithm.h graph.h
SVG.o : SVG.h
TXT.o : TXT.h
vertex.o : vertex.h
via_operations.o : via_operations.h graph.h vertex.h edge.h


$(LINK_TARGET): $(OBJECTS) 
# $@ expands to the rule's target (LINK_TARGET)
# $^ expands to the rule's dependencies (OBJECTS)
# Note that -lm is used because of the dependency on math.h
# gcc -fstack-protector-all -std=c99 -g -o $@ $^ -lm
# gcc -std=c99 -Wall -o $@ $^ -lm
#dell 
	gcc -O3 -o $@ $^ -lm
# mac
# gcc -o $@ $^

%.o : %.c
# $@ for the pattern-matched target
# $< for the pattern-matched dependency
# gcc -fstack-protector-all -std=c99 -g -o $@ -c $<
#gcc -std=c99 -Wall -g -o $@ -c $<
#dell
	gcc -O3 -o $@ -c $< -lm

#mac
# gcc -o $@ -c $<

# Cleaning build environment
clean:
# -f forced deletion 
# -i interacts with the user
# -r recursive removal
# -rf (DO NOT USE!)
# touch is just to prevent error message when file doesn’t exist
	touch $(REBUILDABLES)
	rm $(REBUILDABLES)
	echo done cleaning