#
# Kenneth Palmer
# Kenneth.Palmer@UTDallas.edu
# CS 3377.502
#
# Based on the example Makefile provided by Dr. Perkins
#

CXX = g++
CXXFLAGS = -std=c++11
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 



EXECFILE = Program6

OBJS = main.o

#The specification says that "Your Makefile should pull the project and build," so that's why make automatically defaults to pulling and building
all: build #pull

pull:
	git pull origin master

build: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

commit:
	$(eval MSG := $(shell read -p "Commit message: " msg; echo $$msg))
	git add -A
	git commit -m "$(MSG)"
