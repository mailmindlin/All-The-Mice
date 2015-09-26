# Assumes that you allready have yagarto (http://sourceforge.net/projects/yagarto/) installed
include Config.mk

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(abspath $(notdir $(patsubst %/,%,$(dir $(mkfile_path)))))
KERNEL = $(current_dir)/Kernel
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
winsfix = $(subst /,\,$(1))

CTARGETS = $(patsubst Kernel/%.c, $(BIN)/cpp/%.o, $(call rwildcard, Kernel, *.c))
CPPTARGETS = $(filter-out Kernel/Kernel.o,$(patsubst Kernel/%.cpp, $(BIN)/cpp/%.o, $(call rwildcard, Kernel, *.cpp)))
ASMTARGETS = $(BIN)/asm/memset.o bin/asm/memcpy.o bin/asm/mailbox.o bin/asm/framebuffer.o bin/asm/armmodes.o
BLT = $(BIN)/asm/bootloader.o
BLS = asm/rpi/start.s

# OS-Specific tasks
ifeq ($(OS),Windows_NT)
	RM = rd /Q /S
else
	CPPTARGETS = $(CPPTARGETx)
	include Make_NIX
endif

all: buildAsm buildCpp
	@echo version 5.1
	@echo $(CPP)

buildCpp: $(BIN) $(CPPTARGETS) $(CTARGETS)

buildAsm: $(BIN)/asm $(ASMTARGETS)

bootloader: $(BIN)/asm
	$(AS) $(AFLAGS) -c -o $(BLT) $(BLS)

link:
	$(CPP) $(LDFLAGS) -o $(ELF) Kernel/Kernel.cpp $(BLT) $(ASMTARGETS) $(CPPTARGETS) $(CTARGETS)
	

$(BIN):
	@-mkdir $(BIN)
	@-mkdir $(BIN)/cpp
	@-mkdir $(BIN)/cpp/IO
	@-mkdir $(BIN)/cpp/IO/Display
	@-mkdir $(BIN)/cpp/util

$(BIN)/cpp: $(BIN)
	@md bin\cpp

$(BIN)/asm: $(BIN)
	@-md $(BIN)\asm

$(BIN)/asm/%.o: asm/rpi/%.S
	@echo :building $<
	$(AS) $(AFLAGS) -c -o $@ $<

$(BIN)/cpp/%.o: Kernel/%.c
	@echo :building $<
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN)/cpp/%.o: Kernel/%.cpp
	@echo :building $<
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	@-rd /Q /S $(BIN)