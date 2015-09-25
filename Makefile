# Assumes that you allready have yagarto (http://sourceforge.net/projects/yagarto/) installed
include Config.mk

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(abspath $(notdir $(patsubst %/,%,$(dir $(mkfile_path)))))
KERNEL = $(current_dir)/Kernel
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
winsfix = $(subst /,\,$(1))

CPPTARGETx = $(patsubst %.cpp, $(abspath %.o), $(call rwildcard, Kernel, *.cpp))
ASMTARGETx = asm/rpi/

# OS-Specific tasks
ifeq ($(OS),Windows_NT)
	CPPTARGETS = $(call winsfix, $(CPPTARGETx))
	ASMTARGETS = $(call winsfix, $(ASMTARGETx))
else
	echo "boop"
	CPPTARGETS = $(CPPTARGETx)
	include Make_NIX
endif

all: buildCpp
	@echo version 5.1
	@echo $(CPP)

buildCpp: bin/kernel
	$(CPP) $(CPPFLAGS) -c E:\Documents\GitHub\All-The-Mice\Kernel\Kernel.cpp -o E:\Documents\GitHub\All-The-Mice\bin\kernel\Kernel.o

buildAsm: bin/asm
	

bin:
	mkdir bin

bin/kernel: bin
	@md bin\kernel

bin/asm: bin
	@md bin\asm

%.o: %.S
	$(AS) $(AFLAGS) -c -o $@ $<

%.o: %.c
	@echo building C
	$(CC) $(CFLAGS) -c -o $@ $<

Kernel/%.o: Kernel/%.cpp
	@echo building CPP
	$(CPP) $(CPPFLAGS) -c -o $@ $<