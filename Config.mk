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
PRE = arm-none-eabi- #set to the prefix for yagarto on your computer
CC = $(PRE)gcc
CPP = $(PRE)g++
AS = $(PRE)as
LD = $(PRE)ld
AR = $(PRE)ar
OBJCP = $(PRE)objcopy
OBJDP = $(PRE)objdump
RANLIB = $(PRE)ranlib


#          =============End Config================


ifeq ($(strip $(RPI_REVISION)),2)
	ARCH ?= armv7-a
	TUNE ?= cortex-a7
	FPU  ?= neon-vfpv4
else
	ARCH ?= armv6j
	TUNE ?= arm1176jzf
endif

GFLG = -std=gnu++11 -march=$(strip $(ARCH)) -mtune=$(strip $(TUNE)) -mfloat-abi=hard -D__RPI_MODEL=$(strip $(RPI_MODEL))\
	-D__RPI_REVISION=$(strip $(RPI_REVISION)) -I $(KERNEL) -D__REALCOMP__ -D__arm__
ifdef FPU
	GFLG += -mfpu=$(strip $(FPU))
endif

AFLAGS   ?= $(GFLG) -I $(KERNEL)
CFLAGS   ?= $(GFLG) -undef -Wall -Wextra -Wno-psabi -fsigned-char
CPPFLAGS ?= $(GFLG) -undef -Wall -Wno-psabi -fsigned-char -I Kernel/util -Wno-write-strings
# CFLAGS   ?= $(GFLG) -undef -Wall -Wextra -Wno-psabi -fsigned-char
# CPPFLAGS ?= $(GFLG) -undef -Wall -Wextra -Wno-psabi -fsigned-char 