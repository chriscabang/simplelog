PROJECT		:= simplelog
TARGET	 	:= libsmpllg

ROOT			:= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
SRC_FILES	:= $(wildcard src/*.c)
INCLUDES	:= $(ROOT)/includes
TEST_DIR	:= $(ROOT)/test
LIB_DIR		:= $(ROOT)/lib
BIN_DIR		:= $(ROOT)/bin

DEBUG			:= 1

CC				:= gcc
AR				:= ar

CFLAGS		+= -static
CFLAGS		+= -I$(INCLUDES)
ifdef DEBUG 
	CFLAGS	+= -DDEBUG=$(DEBUG)
endif

prerequisites:
	mkdir -p $(LIB_DIR)

all: prerequisites lib

$(CC): prerequisites

$(TARGET).o: $(SRC_FILES) $(CC)
	$(CC) $(CFLAGS) $< -c -o $(TARGET).o

$(LIB_DIR)/$(TARGET).a: $(TARGET).o
	$(AR) rcs $@ $<

test.o: $(TEST_DIR)/main.c
	$(CC) $(CFLAGS) $< -c -o $@

test: test.o $(LIB_DIR)/$(TARGET).a
	mkdir -p $(BIN_DIR)
	$(CC) -lm -o $(BIN_DIR)/$@ $< -L.$(LIB_DIR)/$(TARGET)

lib: $(LIB_DIR)/$(TARGET).a

.PHONY: all lib test clean help

clean:
	rm -rf $(LIB_DIR) $(BIN_DIR) *.o

help:
	@echo  'Cleaning targets:'
	@echo  '  clean     - delete generated $(BUILD_DIR) directory'
	@echo  ''
	@echo  'Build:'
	@echo  '  all         - Build all targets marked with [*]'
	@echo  '* lib         - Build the bare kernel'
	@echo  '* test        - Build all modules'
	@echo  '  help        - Install all modules to INSTALL_MOD_PATH (default: /)'
	@echo  ''