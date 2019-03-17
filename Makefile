# Syntax:
# target: dependencies
# 	command

# A full, incremental build (also, as first rule, the default)
default: link

# This target is the final compile and depends on other targets
link: bin/main.o bin/my-functions.o
	gcc dist/simulate.o dist/my-functions.o -o dist/simulate

# This target compiles just main.cpp (creates an object file)
bin/main.o: main.c
	gcc -c -Wall main.c -o dist/simulate.o

# This target compiles just lib/my-functions.cpp (create an object file)
bin/my-functions.o: lib/my-functions.c
	gcc -c -Wall lib/my-functions.c -o dist/my-functions.o

# Remove all built files, and re-create the bin directory
clean:
	rm -rf ./dist && mkdir dist
