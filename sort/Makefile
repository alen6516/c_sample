# speficy fake targets. so make won't check if there is a file called "clean"
.PHONY: all clean install

# [target]: [dependency] [dependency]
# 		[rule]
#		[rule]
#
# [target]: [dependency]
# 		[rule]

CC = gcc
CFLAGS = -g
SRC = arr.h main.c bubble_sort.c insert_sort.c quick_sort.c my_quick_sort.c
EXE = a.out

all: $(EXE)

clean:
	rm a.out

a.out:
	$(CC) $(CFLAGS) $(SRC)

# $? : 
# $@ : the target
# $* : current dependent object without extension filename
# $< : current dependent object
