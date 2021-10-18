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
SRC = client.c server.c client_table.c
EXE = client server

all: $(EXE)

clean:
	rm -rf client server

client:
	$(CC) $(CFLAGS) client.c -pthread -o client

server:
	$(CC) $(CFLAGS) server.c client_table.c -o server


# $? : 
# $@ : the target
# $* : current dependent object without extension filename
# $< : current dependent object

