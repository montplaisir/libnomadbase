
ifndef TOP
$(error TOP needs to be defined)
endif
ifndef VARIANT
VARIANT				= release
endif


UNAME := $(shell uname)

BUILD_DIR           = $(TOP)/build/$(VARIANT)
SRC_DIR             = $(TOP)/src
OBJ_DIR             = $(BUILD_DIR)/obj
INCLUDE_DIR         = $(BUILD_DIR)/include/libnomadbase
BIN_DIR             = $(BUILD_DIR)/bin


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


all: $(INCLUDE_DIR)/Util $(OBJ_DIR)/Exception.o $(OBJ_DIR)/utils.o

$(INCLUDE_DIR)/Util: Copyright.hpp  defines.hpp  Exception.hpp  Uncopyable.hpp  utils.hpp 
	@mkdir -p $@
	@cp -f $^ $@

$(OBJ_DIR)/%.o: %.cpp %.hpp
	@mkdir -p $(OBJ_DIR)
	$(COMPILE) $(INCLFLAGS) $(OBJFLAGS) $< -o $@

clean:
	@rm -rf $(INCLUDE_DIR)/Util
	@rm -f $(OBJ_DIR)/Exception.o $(OBJ_DIR)/utils.o
