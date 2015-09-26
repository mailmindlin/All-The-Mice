#          ============Configuration==============

#Raspberry Pi info
#Available models
MODEL_A1  = 0
MODEL_A1P = 1
MODEL_B1  = 2
MODEL_B1P = 3
MODEL_B2  = 4
MODEL_CM  = 5

RPI_MODEL ?= $(MODEL_B1) # May be one of the above defined models
# may be 1 or 2 (2 for model B2, CM, or later; 1 for everything else).
RPI_REVISION ?= 2

#Compiler info
#set to the prefix for yagarto on your computer
PRE = arm-none-eabi-
CC = $(PRE)gcc
CPP = $(PRE)g++
AS = $(PRE)as
LD = $(PRE)ld
AR = $(PRE)ar
OBJCP = $(PRE)objcopy
OBJDP = $(PRE)objdump
RANLIB = $(PRE)ranlib

# File output options
BIN :=  bin
ELF =  $(BIN)/kernel.elf
MAP =  $(BIN)/kernel.map
LIST = $(BIN)/kernel.list
OUT =  $(BIN)/Kernel.img

#          =============End Config================

ifeq ($(strip $(RPI_REVISION)),2)
	ARCH ?= armv7-a
	CPU ?= cortex-a7
	FPU  ?= neon-vfpv4
else
	ARCH ?= armv6j
	CPU ?= arm1176jzf
endif

GFLG = -march=$(strip $(ARCH)) -mfloat-abi=softfp -I $(KERNEL)
ifdef FPU
	GFLG += -mfpu=$(strip $(FPU))
endif

AFLAGS   ?= $(GFLG) -I $(KERNEL) --defsym __RPI_REVISION=$(strip $(RPI_REVISION))  --defsym __RPI_MODEL=$(strip $(RPI_MODEL)) --defsym __REALCOMP__=1\
	-warn --statistics -k -v -mcpu=$(strip $(CPU))
CFLAGS   ?= $(GFLG) -mtune=$(strip $(CPU)) -D__RPI_MODEL=$(strip $(RPI_MODEL)) -D__RPI_REVISION=$(strip $(RPI_REVISION)) -D__REALCOMP__ -D__arm__\
	-std=gnu++11 -Wall -Wextra -Wno-psabi -fsigned-char -ftree-vectorize -ffast-math
CPPFLAGS ?= $(CFLAGS) -I Kernel/util -Wno-write-strings
LDFLAGS ?= $(CPPFLAGS) -I $(BIN)/cpp -I $(BIN)/asm -I Kernel -I asm/rpi \
	-fPIC -ffreestanding -Wextra -nostartfiles -fexceptions -v \
	-Wl,-T,linker/rpi.ld -Wl,-Map,$(MAP) -Wl,-static -Wl,--gc-sections -Wl,--verbose -Wa,-mcpu=$(CPU)
# CFLAGS   ?= $(GFLG) -undef -Wall -Wextra -Wno-psabi -fsigned-char
# CPPFLAGS ?= $(GFLG) -undef -Wall -Wextra -Wno-psabi -fsigned-char 