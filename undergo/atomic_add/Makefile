# speficy fake targets. so make won't check if there is a file called "clean"
.PHONY: all clean install

# [target]: [dependency] [dependency]
# 		[rule]
#		[rule]
#
# [target]: [dependency]
# 		[rule]

CC = gcc
CFLAGS = -g -pthread
SRC = main.c atomic_type_add.c atomic_long_add.c atomic_add.c sync_add.c mutex_lock_add.c spin_lock_add.c spin_trylock_add.c
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
