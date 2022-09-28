LINK_TARGET1 = progrdin 
LINK_TARGET2 = progrest

OBJECTS = SVG.o TXT.o path.o main.o 
OTHER_OBJECTS1 = list_dynamic.o
OTHER_OBJECTS2 = list_static.o 

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS) $(OTHER_OBJECTS1) $(OTHER_OBJECTS2) $(LINK_TARGET1) $(LINK_TARGET2)

progr: $(LINK_TARGET1) $(LINK_TARGET2)
	echo All done


# Dependencies
list_dynamic.o : list.h
list_static.o : list.h 
SVG.o : SVG.h
path.o : path.h
main.o : list.h SVG.h path.h


$(LINK_TARGET1): $(OBJECTS) $(OTHER_OBJECTS1)
# $@ expands to the rule's target (LINK_TARGET1)
# $^ expands to the rule's dependencies (OBJECTS) (OTHER_OBJECTS1)
	gcc -fstack-protector-all -std=c99 -o $@ $^

$(LINK_TARGET2): $(OBJECTS) $(OTHER_OBJECTS2) 
# $@ expands to the rule's target (LINK_TARGET2)
# $^ expands to the rule's dependencies (OBJECTS) (OTHER_OBJECTS2)
	gcc -fstack-protector-all -std=c99 -o $@ $^

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


