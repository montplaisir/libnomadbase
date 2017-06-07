
#TOP is the base directory for libnomadbase. This is where the src directory is located.

ifndef TOP
$(error TOP needs to be defined)
endif
ifndef BUILD_DIR
$(error BUILD_DIR needs to be defined)
endif

SRC_DIR             = $(TOP)/src
INCLUDE_DIR         = $(BUILD_DIR)/include/libnomadbase
OBJ_DIR             = $(BUILD_DIR)/obj
LIB_DIR             = $(BUILD_DIR)/lib

#VRM I don't know how to avoid listing all objects to compile the library.
OBJ_LIB             = Double.o Exception.o LHS.o Parameters.o Param.o \
                      ParamValue.o Point.o RNG.o fileutils.o utils.o Vector.o
OBJ_LIB             := $(addprefix $(OBJ_DIR)/,$(OBJ_LIB))


CXXFLAGS_LIBS       =
ifeq ($(UNAME), Darwin)
#VRM can we get the version number from somewhere else?
LIB_CURRENT_VERSION = 4.0.0
CXXFLAGS_LIBS       = -current_version $(LIB_CURRENT_VERSION) -compatibility_version $(LIB_CURRENT_VERSION) -install_name $(LIB_DYNAMIC_NAME) -headerpad_max_install_names
endif
ifeq ($(UNAME), Linux)
CXXFLAGS_LIBS       += -Wl,-soname,'$(LIB_DYNAMIC_NAME)' -Wl,-rpath-link,'.' -Wl,-rpath,'$$ORIGIN'
endif

CXXFLAGS            = -O2 -ansi -Wall -fPIC
INCLFLAGS           = -I$(INCLUDE_DIR)

COMPILE             = g++ $(CXXFLAGS) $(INCLFLAGS)

LIB_DYNAMIC_NAME    = libnomadbase.so.4.0.0
LIB_DYNAMIC         = $(LIB_DIR)/$(LIB_DYNAMIC_NAME)


#NOTE: Util has to be made before Math, and Math before Param.
all: $(INCLUDE_DIR)
	$(MAKE) $(INCLUDE_DIR)
	@cd Util && $(MAKE) all TOP=$(TOP)
	@cd Math && $(MAKE) all TOP=$(TOP)
	@cd Param && $(MAKE) all TOP=$(TOP)
	#@cd events_sandbox && $(MAKE) all TOP=$(TOP)
	$(MAKE) $(LIB_DYNAMIC)

$(INCLUDE_DIR): nomad_nsbegin.hpp nomad_nsend.hpp nomad_nsuse.hpp nomad_version.hpp
	mkdir -p $@
	cp -f $^ $@

$(LIB_DYNAMIC): $(OBJ_LIB) $(INCLUDE_DIR)
	@mkdir -p $(LIB_DIR)
	$(COMPILE) -shared -o $(LIB_DYNAMIC) $(OBJ_LIB) $(CXXFLAGS_LIBS)
ifeq ($(UNAME), Darwin)
	@install_name_tool -change $(LIBSGTELIB_NAME) @loader_path/$(LIBSGTELIB_NAME) $(LIB)
endif

clean:
	@echo "   cleaning trash files"
	@rm -f core *~
	@rm -rf $(INCLUDE_DIR)
	@rm -f $(LIB_DYNAMIC)
	@cd Util && $(MAKE) clean TOP=$(TOP)
	@cd Math && $(MAKE) clean TOP=$(TOP)
	@cd Param && $(MAKE) clean TOP=$(TOP)
	#@cd events_sandbox && $(MAKE) clean TOP=$(TOP)
