# speficy fake targets. so make won't check if there is a file called "clean"
.PHONY: all clean install

# [target]: [dependency] [dependency]
# 		[rule]
#		[rule]
#
# [target]: [dependency]
# 		[rule]

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -Wextra

# Source files
SRC = main.c my_bheap_sort.c bheap_sort.c bubble_sort.c insert_sort.c selection_sort.c quick_sort.c my_quick_sort.c #oop_quick_sort.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = a.out

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Rule for compiling C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm $(OBJ) $(TARGET)

# $? : Prerequisites that are newer than the target (used for dependencies) (eg, foo.c if newer)
# $@ : the target (eg, main.o)
# $* : current dependent object without extension filename (eg, foo)
# $< : current dependent object (eg, foo.c)
# $^ : All dependents (space-separated), with duplicates removed (eg, main.c foo.c)
