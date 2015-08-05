# Current directory
ROOT?=$(shell pwd)/
# For the binary files
BIN?=$(ROOT)bin/
EMULATOR?=$(ROOT)qemu
# Not really used
JBIN?=$(BIN)java/
# For the compiled assembly files
ABIN?=$(BIN)asm/
# For the compiled C++ libraries
CBIN?=$(BIN)cpp/
# Where the java source code is
JSRC?=$(ROOT)java/
# Assembly source code
ASRC?=$(ROOT)asm/rpi
# C++ source code
CSRC?=$(ROOT)Kernel
# linker script source
LSRC?=$(ROOT)linker/
# Output binary
OUT?=$(BIN)Kernel.img
ARGS?=
# You can compile for the raspberry pi version 2 by specifying 'TARGET=rpi2' in the command line.
# Otherwise, it defaults to rpi
ARCH?=armv6
TARGET?=rpi1
MAKER?=$(JBIN)Make.jar
JFLAGS=-arch $(ARCH) -targ $(TARGET) --src-asm $(ASRC) --src-java $(JSRC) --src-c++ $(CSRC) --src-ld $(LSRC) --bin-asm $(ABIN) --bin $(BIN) --bin-java $(JBIN) --bin-asm $(ABIN) -o $(OUT) $(ARGS)
MK?=java -jar $(MAKER) $(JFLAGS)
all: init
	$(MK) clean build check
about: init
	$(MK) about

build: init
	$(MK) build

check: init
	$(MK) check

clean: init
	$(MK) clean $(JFLAGS)

compile: init
	$(MK) compile

link: init
	$(MK) link

emulate:
	$(MAKE) -C $(EMULATOR) BIN=$(BIN)

#this should copy the kernel to a SD card inserted into a linux/mac machine. TODO: fix for windows
mount: init
	rm -f /Volumes/BOOT/Kernel.img
	cp $(OUT) /Volumes/BOOT/Kernel.img
	diskutil eject /dev/disk1 #fix ejecting the disk

init: