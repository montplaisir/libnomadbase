
ifndef TOP
$(error TOP needs to be defined)
endif
ifndef ($(VARIANT))
VARIANT             = release
endif

UNAME := $(shell uname)

BUILD_DIR           = $(TOP)/build/$(VARIANT)
SRC_DIR             = $(TOP)/src
INCLUDE_DIR         = $(BUILD_DIR)/include
OBJ_DIR             = $(BUILD_DIR)/obj
BIN_DIR             = $(BUILD_DIR)/bin

MATH_DIRNAME		= Math


ifeq ($(VARIANT), release)
CXXFLAGS            = -O2
else
CXXFLAGS            = -g
endif
CXXFLAGS            += -Wall -fpic
ifeq ($(UNAME), Linux)
CXXFLAGS            += -ansi
endif
OBJFLAGS            = -c

INCLFLAGS			= -I$(INCLUDE_DIR)

COMPILE             = g++ $(CXXFLAGS)


all: $(OBJ_DIR)/Double.o $(OBJ_DIR)/LHS.o $(OBJ_DIR)/Point.o $(OBJ_DIR)/RNG.o \
		$(OBJ_DIR)/Vector.o

$(OBJ_DIR)/%.o: %.cpp %.hpp
	@mkdir -p $(INCLUDE_DIR)/$(MATH_DIRNAME)
	@mkdir -p $(OBJ_DIR)
	@cp *.hpp  $(INCLUDE_DIR)/$(MATH_DIRNAME)
	$(COMPILE) $(INCLFLAGS) $(OBJFLAGS) $< -o $@

clean:
	@rm -f $(OBJ_DIR)/Double.o $(OBJ_DIR)/LHS.o $(OBJ_DIR)/Point.o \
		$(OBJ_DIR)/RNG.o $(OBJ_DIR)/Vector.o
	@rm -rf $(INCLUDE_DIR)/$(MATH_DIRNAME)
