
# Ref: googletest.1.8.0/googletest/make/Makefile

# Points to the root of Google Test
#GTEST_DIR = ../../googletest.1.8.0/googletest

ifndef GTEST_DIR
$(error GTEST_DIR (path to googletest directory) needs to be defined)
endif

ifndef BUILD_DIR
ifdef TOP
VARIANT             = release
BUILD_DIR           = $(TOP)/build/$(VARIANT)
$(info Setting BUILD_DIR to $(BUILD_DIR))
else
$(error BUILD_DIR needs to be defined)
endif
endif


# Where to find user code.
OBJ_DIR             = $(BUILD_DIR)/obj
INCLUDE_DIR         = $(BUILD_DIR)/include/libnomadbase
LIB_DIR             = $(BUILD_DIR)/lib
BIN_DIR             = $(BUILD_DIR)/bin

# Where to find unit tests
UNIT_TESTS_DIR		= $(CURDIR)

# Where to write binary output from this makefile
BUILD_TEST_DIR		= $(BUILD_DIR)/test
OBJ_TEST_DIR		= $(BUILD_TEST_DIR)/obj
BIN_TEST_DIR		= $(BUILD_TEST_DIR)/bin

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
#
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

INCLFLAGS = -I$(INCLUDE_DIR)

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = double_unittest point_unittest vector_unittest lhs_unittest
TESTS := $(addprefix $(BIN_TEST_DIR)/,$(TESTS))

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) $(OBJ_TEST_DIR)/gtest.a $(OBJ_TEST_DIR)/gtest_main.a $(OBJ_TEST_DIR)/*.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(OBJ_TEST_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc \
            -o $@

$(OBJ_TEST_DIR)/gtest_main.o : $(GTEST_SRCS_)
	mkdir -p $(OBJ_TEST_DIR)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc \
            -o $@

$(OBJ_TEST_DIR)/gtest.a : $(OBJ_TEST_DIR)/gtest-all.o
	mkdir -p $(OBJ_TEST_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_TEST_DIR)/gtest_main.a : $(OBJ_TEST_DIR)/gtest-all.o $(OBJ_TEST_DIR)/gtest_main.o
	mkdir -p $(OBJ_TEST_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_TEST_DIR)/double_unittest.o : $(UNIT_TESTS_DIR)/double_unittest.cpp \
                     $(INCLUDE_DIR)/Math/Double.hpp $(GTEST_HEADERS)
	mkdir -p $(OBJ_TEST_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLFLAGS) -c $(UNIT_TESTS_DIR)/double_unittest.cpp \
            -o $@

$(OBJ_TEST_DIR)/point_unittest.o : $(UNIT_TESTS_DIR)/point_unittest.cpp \
                     $(INCLUDE_DIR)/Math/Point.hpp $(GTEST_HEADERS)
	mkdir -p $(OBJ_TEST_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLFLAGS) -c $(UNIT_TESTS_DIR)/point_unittest.cpp \
            -o $@

$(OBJ_TEST_DIR)/vector_unittest.o : $(UNIT_TESTS_DIR)/vector_unittest.cpp \
                     $(INCLUDE_DIR)/Math/Vector.hpp $(GTEST_HEADERS)
	mkdir -p $(OBJ_TEST_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLFLAGS) -c $(UNIT_TESTS_DIR)/vector_unittest.cpp \
            -o $@

$(OBJ_TEST_DIR)/lhs_unittest.o : $(UNIT_TESTS_DIR)/lhs_unittest.cpp \
                     $(INCLUDE_DIR)/Math/LHS.hpp $(GTEST_HEADERS)
	mkdir -p $(OBJ_TEST_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLFLAGS) -c $(UNIT_TESTS_DIR)/lhs_unittest.cpp \
            -o $@


$(BIN_TEST_DIR)/% : $(OBJ_TEST_DIR)/%.o \
                        $(LIB_DIR)/libnomadbase.so.4.0.0 $(OBJ_TEST_DIR)/gtest_main.a
	mkdir -p $(BIN_TEST_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

run: $(TESTS)
	$(UNIT_TESTS_DIR)/run_tests.sh $(BIN_TEST_DIR)















