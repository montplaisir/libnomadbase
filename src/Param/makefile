UNAME := $(shell uname)
VARIANT             = release

ifndef TOP
$(error TOP needs to be defined)
endif

BUILD_DIR           = $(TOP)/build/$(VARIANT)
SRC_DIR             = $(TOP)/src
INCLUDE_DIR         = $(BUILD_DIR)/include
OBJ_DIR             = $(BUILD_DIR)/obj
BIN_DIR             = $(BUILD_DIR)/bin

CXXFLAGS            = -O2 -ansi -Wall -fpic
INCLFLAGS           = -I$(INCLUDE_DIR)
OBJFLAGS            = -c

COMPILE             = g++ $(CXXFLAGS) $(INCLFLAGS)


all: $(INCLUDE_DIR)/Param $(OBJ_DIR)/ParamValue.o $(OBJ_DIR)/Param.o $(OBJ_DIR)/Parameters.o

$(INCLUDE_DIR)/Param: ParamValue.hpp Param.hpp Parameters.hpp
	@mkdir -p $@
	@cp -f $^ $@

$(OBJ_DIR)/ParamValue.o: ParamValue.hpp ParamValue.cpp
	$(COMPILE) $(OBJFLAGS) ParamValue.cpp -o $@

$(OBJ_DIR)/Param.o: Param.cpp Param.hpp 
	$(COMPILE) $(OBJFLAGS) Param.cpp -o $@

$(OBJ_DIR)/Parameters.o: Parameters.cpp Parameters.hpp 
	$(COMPILE) $(OBJFLAGS) Parameters.cpp -o $@

clean:
	@rm -rf $(INCLUDE_DIR)/Param
	@rm -f $(OBJ_DIR)/ParamValue.o $(OBJ_DIR)/Param.o $(OBJ_DIR)/Parameters.o
