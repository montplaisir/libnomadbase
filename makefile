
#TOP is the base directory for libnomadbase. This is where the src directory is located.

ifdef TOP
$(warning TOP modified to $(CURDIR))
endif
TOP					= $(CURDIR)

ifndef BUILD_DIR
$(error BUILD_DIR must be defined. This is the base folder where the library will be compiled.)
endif

SRC_DIR             = $(TOP)/src
UNIT_TESTS_DIR      = $(TOP)/unit_tests
BUILD_TEST_DIR      = $(BUILD_DIR)/test
OBJ_TEST_DIR        = $(BUILD_TEST_DIR)/obj
BIN_TEST_DIR        = $(BUILD_TEST_DIR)/bin


all:
	cd $(SRC_DIR) && $(MAKE) all TOP=$(TOP)
	cd $(UNIT_TESTS_DIR) && $(MAKE) all && $(MAKE) run

clean:
	cd $(SRC_DIR) && $(MAKE) clean TOP=$(TOP)
	cd $(UNIT_TESTS_DIR) && $(MAKE) clean TOP=$(TOP)

