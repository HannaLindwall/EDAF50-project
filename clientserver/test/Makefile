# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = $(CXX)

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS  = -std=c++11 -I..
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++11 
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS   = -g -L..
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Libraries
LDLIBS = -lclientserver

# Targets
PROGS = myserver myclient

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
# The dependency on libclientserver.a is not defined.
myserver: myserver.o  
myclient: myclient.o

# Phony targets
.PHONY: all clean distclean

# Standard clean
clean:
	rm -f *.o $(PROGS)

distclean: clean
	-rm *.d


# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
