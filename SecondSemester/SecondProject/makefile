LINK_TARGET = t2

OBJECTS = main.o commandline.o path.o list_dynamic.o graph.o dijkstras_algorithm.o ascending_priority_queue.o descending_priority_queue.o via_operations.o vertex.o edge.o _auxiliary_functions.o hash_table.o mM_avl_tree_wlist.o rectangle.o block.o TXT.o _string_editing.o geo_operations.o SVG.o output_svg.o qry_operations.o qry_catac.o qry_p_.o qry_o_.o property.o _geometry_operations.o qry_cx.o kruskals_algorithm.o qry_rv.o disjoint_sets.o

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
main.o : dijkstras_algorithm.h graph.h commandline.h path.h geo_operations.h hash_table.h mM_avl_tree_wlist.h qry_operations.h
commandline.o : commandline.h
path.o : path.h
list_dynamic.o : list.h
graph.o : graph.h list.h 
dijkstras_algorithm.o : dijkstras_algorithm.h graph.h list.h ascending_priority_queue.h
ascending_priority_queue.o : ascending_priority_queue.h descending_priority_queue.h
descending_priority_queue.o : descending_priority_queue.h
via_operations.o : via_operations.h graph.h vertex.h edge.h
vertex.o : vertex.h
edge.o : edge.h
geo_operations.o : geo_operations.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h _auxiliary_functions.h
_auxiliary_functions.o : _auxiliary_functions.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h TXT.h
hash_table.o : hash_table.h list.h
mM_avl_tree_wlist.o : mM_avl_tree_wlist.h list.h
rectangle.o : rectangle.h
block.o : block.h _string_editing.h
TXT.o : TXT.h
_string_editing.o : _string_editing.h
SVG.o : SVG.h
output_svg.o : output_svg.h SVG.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h vertex.h edge.h
qry_operations.o : qry_operations.h SVG.h TXT.h qry_catac.h output_svg.h path.h graph.h qry_p_.h qry_o_.h property.h output_svg.h qry_cx.h
qry_p_.o : qry_p_.h property.h dijkstras_algorithm.h
qry_o_.o : qry_o_.h property.h SVG.h
qry_catac.o : qry_catac.h
property.o : property.h
_geometry_operations.o : _geometry_operations.h
kruskals_algorithm.o : kruskals_algorithm.h graph.h disjoint_sets.h ascending_priority_queue.h
disjoint_sets.o : disjoint_sets.h
qry_rv.o : qry_rv.h graph.h vertex.h edge.h rectangle.h _geometry_operations.h kruskals_algorithm.h
qry_cx.o : qry_cx.h graph.h vertex.h edge.h _auxiliary_functions.h SVG.h

$(LINK_TARGET): $(OBJECTS) 
# $@ expands to the rule's target (LINK_TARGET)
# $^ expands to the rule's dependencies (OBJECTS)
# Note that -lm is used because of the dependency on math.h
# gcc -fstack-protector-all -std=c99 -g -o $@ $^ -lm
# gcc -std=c99 -Wall -o $@ $^ -lm
	gcc -o $@ $^

%.o : %.c
# $@ for the pattern-matched target
# $< for the pattern-matched dependency
# gcc -fstack-protector-all -std=c99 -g -o $@ -c $<
#gcc -std=c99 -Wall -g -o $@ -c $<
	gcc -o $@ -c $<

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