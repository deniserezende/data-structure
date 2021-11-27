LINK_TARGET = exec

OBJECTS = main_graph_algor.o list_dynamic.o graph.o ascending_priority_queue.o descending_priority_queue.o graph_algorithms.o


# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
main_graph_algor.o : graph_algorithms.h graph.h
list_dynamic.o : list.h
graph.o : list.h 
graph_algorithms.o : graph_algorithms.h graph.h list.h ascending_priority_queue.h
ascending_priority_queue.o : ascending_priority_queue.h descending_priority_queue.h
descending_priority_queue.o : descending_priority_queue.h

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