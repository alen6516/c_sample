# it is a test
all: hello.out

# declare variables
SHELL = /bin/bash
CC = gcc
INSTDIR = /tmp/
INCLUDE = .
CFLAGS = -g -Wall -ansi
LIBS += -framework CoreFoundation

hello.out: hello.o
	$(CC) -o hello.out hello.o

hello.o: hello.c a.h
	$(CC) -I$(INCLUDE) $(CFLAG) -c hello.c

clean:
	rm *.o *.out

install: mytest
	@echo "here execute shell script";
	@#if [ -d $(INSTDIR) ] \
	#then	\
	#    cp hello.out $(INSTDIR) \
	#    chmod a+x $(INSTDIR)/hello.out \
	#    chmod og-w $(INSTDIR)/hello.out \
	#    echo "Installed in $(INSTDIR)" \
	#else \
	#    echo "Sorry, $(INSTDIR) does not exist" \
	#fi
