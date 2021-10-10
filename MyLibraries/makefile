LINK_TARGET = progr

OBJECTS = main.o geooperations.o qryoperations.o geometry_operations.o dpi_dr.o fg.o im_t30_nve.o output_svg.o output_txt.o commandline.o person.o building.o meteor.o path.o kd_tree.o binary_search_tree.o list_dynamic.o TXT.o SVG.o rectangle.o circle.o segment.o
 
# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
main.o : commandline.h path.h geooperations.h qryoperations.h kd_tree.h rectangle.h circle.h TXT.h SVG.h output_svg.h
geooperations.o : geooperations.h kd_tree.h rectangle.h circle.h building.h person.h
qryoperations.o : qryoperations.h kd_tree.h list.h rectangle.h circle.h segment.h building.h person.h meteor.h geometry_operations.h dpi_dr.h fg.h im_t30_nve.h TXT.h SVG.h output_svg.h
geometry_operations.o : geometry_operations.h rectangle.h circle.h segment.h
dpi_dr.o : dpi_dr.h kd_tree.h binary_search_tree.h rectangle.h building.h geometry_operations.h TXT.h output_txt.h
fg.o : fg.h kd_tree.h binary_search_tree.h rectangle.h circle.h building.h person.h geometry_operations.h TXT.h output_txt.h
im_t30_nve.o : im_t30_nve.h kd_tree.h list.h rectangle.h circle.h segment.h person.h meteor.h geometry_operations.h TXT.h output_txt.h
output_svg.o : output_svg.h SVG.h kd_tree.h list.h rectangle.h circle.h person.h building.h meteor.h
output_txt.o : output_txt.h TXT.h binary_search_tree.h rectangle.h circle.h
commandline.o : commandline.h
person.o : person.h
building.o : building.h
meteor.o : meteor.h
path.o : path.h
kd_tree.o : kd_tree.h
binary_search_tree.o : binary_search_tree.h
list_dynamic.o : list.h
TXT.o : TXT.h
SVG.o : SVG.h
rectangle.o : rectangle.h
circle.o : circle.h
segment.o : segment.h


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


