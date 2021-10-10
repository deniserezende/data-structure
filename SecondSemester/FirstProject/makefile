LINK_TARGET = t1

OBJECTS = main.o commandline.o path.o pm_operations.o geo_operations.o qry_operations.o hash_table.o mM_avl_tree_wlist.o list_dynamic.o rectangle.o person.o property.o block.o string_editing.o output_svg.o SVG.o TXT.o _auxiliary_functions.o qry_del_m_dm_mud.o qry_dmpt_catac.o qry_property_lease.o qry_mul_hom.o

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
main.o: commandline.h path.h pm_operations.h geo_operations.h qry_operations.h hash_table.h mM_avl_tree_wlist.h output_svg.h SVG.h TXT.h
commandline.o: commandline.h
path.o: path.h
pm_operations.o: hash_table.h person.h property.h
geo_operations.o: hash_table.h mM_avl_tree_wlist.h rectangle.h block.h _auxiliary_functions.h
qry_operations.o : qry_operations.h SVG.h TXT.h qry_del_m_dm_mud.h qry_dmpt_catac.h qry_property_lease.h qry_mul_hom.h
hash_table.o: hash_table.h list.h
mM_avl_tree_wlist.o: mM_avl_tree_wlist.h list.h
list_dynamic.o: list.h
rectangle.o: rectangle.h
person.o: person.h string_editing.h
property.o: property.h string_editing.h
block.o: block.h string_editing.h
string_editing.o : string_editing.h
output_svg.o : SVG.h hash_table.h rectangle.h block.h property.h person.h mM_avl_tree_wlist.h
SVG.o : SVG.h	
TXT.o : TXT.h
qry_del_m_dm_mud.o : qry_del_m_dm_mud.h hash_table.h rectangle.h block.h property.h person.h _auxiliary_functions.h SVG.h TXT.h
qry_dmpt_catac.o  : qry_dmpt_catac.h hash_table.h rectangle.h block.h property.h person.h _auxiliary_functions.h SVG.h TXT.h
qry_property_lease.o : qry_property_lease.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h property.h person.h _auxiliary_functions.h TXT.h SVG.h
_auxiliary_functions.o : _auxiliary_functions.h hash_table.h mM_avl_tree_wlist.h rectangle.h block.h property.h person.h
qry_mul_hom.o : qry_mul_hom.h hash_table.h mM_avl_tree_wlist.h block.h property.h person.h _auxiliary_functions.h SVG.h TXT.h


$(LINK_TARGET): $(OBJECTS) 
# $@ expands to the rule's target (LINK_TARGET)
# $^ expands to the rule's dependencies (OBJECTS)
# Note that -lm is used because of the dependency on math.h
	gcc -fstack-protector-all -std=c99 -o $@ $^ -lm

%.o : %.c
# $@ for the pattern-matched target
# $< for the pattern-matched dependency
	gcc -fstack-protector-all -std=c99 -o $@ -c $<

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


