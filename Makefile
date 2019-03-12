# See versions 1 and 2 (this) on Moodle for
# version with and without variables

# Variables
CC      = gcc
CFLAGS  = -c -Wall
LIBDIR  = lib
BINDIR  = bin
OBJECTS = bin/main.o\
					bin/my-functions.o

# Syntax:
# target: dependencies
# 	command

# A full, incremental build (also, as first rule, the default)
default: link

# This target is the final compile and depends on other targets
link: $(OBJECTS)
	$(CC) $? -o $(BINDIR)/main

# This target compiles just main.cpp (creates an object file)
$(BINDIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(BINDIR)/main.o

# This target compiles just $(LIBDIR)/my-functions.cpp (create an object file)
$(BINDIR)/my-functions.o: $(LIBDIR)/my-functions.c
	$(CC) $(CFLAGS) $(LIBDIR)/my-functions.c -o $(BINDIR)/my-functions.o

# Remove all built files, and re-create the bin directory
clean:
	rm -rf ./$(BINDIR) && mkdir $(BINDIR)