# Set to appropriate C++ compiler
CCC := icpc
CPPFLAGS := -g -std=c++0x -fopenmp

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

# required external library
LIBEXT =  ./tecio/libtecio.a

# standard library
LINK_LIBS= -lgfortran -lpthread -lm -mkl

AVG=$(BINDIR)/average.bin
Q=$(BINDIR)/q.bin
F2P=$(BINDIR)/field2points.bin
	
all: $(AVG) $(Q) $(F2P)

$(AVG): $(OBJ) $(AVGOBJ)
	$(CCC) $(CPPFLAGS) $(INCLUDES) $(OBJ) $(AVGOBJ) -o $(AVG) $(LIBEXT) $(LINK_LIBS)

$(Q): $(OBJ) $(QOBJ)
	$(CCC) $(CPPFLAGS) $(INCLUDES) $(OBJ) $(QOBJ) -o $(Q) $(LIBEXT) $(LINK_LIBS)

$(F2P): $(OBJ) $(F2POBJ)
	$(CCC) $(CPPFLAGS) $(INCLUDES) $(OBJ) $(F2POBJ) -o $(F2P) $(LIBEXT) $(LINK_LIBS)
	
# Compile all source files .cpp into .o files
$(TARGETDIR)/%.o: $(TARGETDIR)/%.cpp
	$(CCC) $(CPPFLAGS) $(INCLUDES) -o $@ -c $<

# Clean target deletes all generated files
REBUILDABLES = $(OBJ) $(BINDIR)/$(AVG) $(BINDIR)/$(Q) $(AVGOBJ) $(QOBJ)
clean:
	rm -f $(REBUILDABLES)
