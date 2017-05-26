
ifndef TOP
TOP					= $(CURDIR)
endif

ifndef VARIANT
VARIANT             = release
endif

BUILD_DIR           = $(TOP)/build/$(VARIANT)
SRC_DIR             = $(TOP)/src
INCLUDE_DIR         = $(BUILD_DIR)/include
OBJ_DIR             = $(BUILD_DIR)/obj
BIN_DIR             = $(BUILD_DIR)/bin


all:
	cd $(SRC_DIR) && $(MAKE) all TOP=$(TOP)

clean:
	@echo "   cleaning trash files"
	@rm -f core *~
	cd $(SRC_DIR) && $(MAKE) clean TOP=$(TOP)
	@rm -rf $(TOP)/build

