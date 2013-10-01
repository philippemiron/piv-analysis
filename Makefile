# Set to appropriate C++ compiler
CCC := g++
CPPFLAGS := -O3 -arch x86_64 -fopenmp -std=gnu++11

# define the target directories.
TARGETDIR=.
SRCDIR=src
BINDIR=bin
# OBJS =  $(TARGETDIR)/$(patsubst %.cpp,%.o,$(wildcard *.cpp))
AVGOBJ := average.o
QOBJ := q.o
F2POBJ := field2points.o
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))


# include directories and external libraries
INCLUDES = -I/opt/local/include/ -I./tecio/tecsrc -I./src
LIBEXT = ./tecio/libtecio.a

AVG=$(BINDIR)/average.bin
Q=$(BINDIR)/q.bin
F2P=$(BINDIR)/field2points.bin
	
all: $(AVG) $(Q) $(F2P)

$(AVG): $(OBJ) $(AVGOBJ)
	$(CCC) $(CPPFLAGS) $(INCLUDES) $(LIBEXT) $(OBJ) $(AVGOBJ) -o $(AVG)  

$(Q): $(OBJ) $(QOBJ)
	$(CCC) $(CPPFLAGS) $(INCLUDES) $(LIBEXT) $(OBJ) $(QOBJ) -o $(Q)  

$(F2P): $(OBJ) $(F2POBJ)
	$(CCC) $(CPPFLAGS) $(INCLUDES) $(LIBEXT) $(OBJ) $(F2POBJ) -o $(F2P)
	
# Compile all source files .cpp into .o files
$(TARGETDIR)/%.o: $(TARGETDIR)/%.cpp
	$(CCC) $(INCLUDES) $(CPPFLAGS) -o $@ -c $<

# Clean target deletes all generated files
REBUILDABLES = $(OBJ) $(BINDIR)/$(AVG) $(BINDIR)/$(Q) $(AVGOBJ) $(QOBJ)
clean:
	rm -f $(REBUILDABLES)