
#TOP is the base directory for libnomadbase. This is where the src directory is located.

ifdef TOP
$(warning TOP modified to $(CURDIR))
endif
TOP					= $(CURDIR)

ifndef BUILD_DIR
$(error BUILD_DIR must be defined. This is the base folder where the library will be compiled.)
endif

SRC_DIR             = $(TOP)/src


all:
	cd $(SRC_DIR) && $(MAKE) all TOP=$(TOP)

clean:
	cd $(SRC_DIR) && $(MAKE) clean TOP=$(TOP)

