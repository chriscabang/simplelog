PROJECT		:= simplelog
TARGET	 	:= lib$(PROJECT)

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
CFLAGS		+= -lstdc++
CFLAGS		+= -I$(INCLUDES)
ifdef DEBUG 
	CFLAGS	+= -DDEBUG=$(DEBUG)
endif

prerequisites:
	mkdir -p $(LIB_DIR)

all: prerequisites lib test

$(CC): prerequisites

$(TARGET).o: $(SRC_FILES) $(CC)
	$(CC) $(CFLAGS) $< -c -o $(TARGET).o

$(LIB_DIR)/$(TARGET).a: $(TARGET).o
	$(AR) rcs $@ $<

test.o: $(TEST_DIR)/main.c
	$(CC) $(CFLAGS) $< -c -o $@

$(BIN_DIR)/test: test.o $(LIB_DIR)/$(TARGET).a
	mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

.PHONY: all lib test clean help

lib: $(LIB_DIR)/$(TARGET).a
test: $(BIN_DIR)/test

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
	@echo  '  help        - You're here'
	@echo  ''