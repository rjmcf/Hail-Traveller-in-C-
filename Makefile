# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = googletest

# Where to find user code.
IDIR = src/header
SDIR = src/impl
ODIR = src/obj
TSDIR = test/impl
TODIR = test/obj
GTDUMP = gtestfiles

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = 

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : testAll

.PHONY : clean
clean :
	rm -f testAll $(TESTS) $(GTDUMP)/* $(ODIR)/* $(TODIR)/*

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(GTDUMP)/gtest-all.o : $(GTEST_DIR)/src/gtest-all.cc $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c -o $@ $<            

$(GTDUMP)/gtest_main.o : $(GTEST_DIR)/src/gtest_main.cc $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c -o $@ $<             

$(GTDUMP)/gtest.a : $(GTDUMP)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(GTDUMP)/gtest_main.a : $(GTDUMP)/gtest-all.o $(GTDUMP)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

# Add object file names here
_OBJ = item location planet
OBJ = $(patsubst %,$(ODIR)/%.o,$(_OBJ))

$(ODIR)/%.o : $(SDIR)/%.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< -I$(IDIR)
	
# Add test object file names here
_TEST = $(patsubst %,%_tests.o,$(_OBJ))
TEST = $(patsubst %,$(TODIR)/%,$(_TEST))

$(TODIR)/%.o : $(TSDIR)/%.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< -I$(IDIR)

testAll : $(OBJ) $(TEST) $(GTDUMP)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
	
.PHONY : run_tests
run_tests : testAll
	./testAll
	$(MAKE) clean
