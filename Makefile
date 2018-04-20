#
# Kenneth Palmer
# Kenneth.Palmer@UTDallas.edu
# CS 3377.502
#
# Based on the example Makefile provided by Dr. Perkins
#

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 



EXECFILE = Program6

OBJS = main.o


all: pull $(EXECFILE)

pull:
	git pull

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

commit:
	MSG ?= $(shell read -p "Commit message: " msg; echo $$msg)
	git add -A
	git commit -m "$(MSG)"
