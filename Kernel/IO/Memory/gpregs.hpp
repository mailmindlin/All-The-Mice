/**
 * gpregs.h
 *
 *  Created on: Sep 25, 2015
 *      Author: mailmindlin
 */

#ifndef IO_MEMORY_GPREGS_HPP_
#define IO_MEMORY_GPREGS_HPP_

#include "memtypes.hpp"

namespace MemoryMap {
struct GPREGS {
	REG32RW GPFSEL0		: 32;
	REG32RW GPFSEL1		: 32;
	REG32RW GPFSEL2		: 32;
	REG32RW GPFSEL3		: 32;
	REG32RW GPFSEL4		: 32;
	REG32RW GPFSEL5		: 32;
	RESRV32 RESERVED0	: 32;
	REG32WO GPSET0		: 32;
	REG32WO GPSET1		: 32;
	RESRV32 RESERVED1	: 32;
	REG32WO GPCLR0		: 32;
	REG32WO GPCLR1		: 32;
	RESRV32 RESERVED2	: 32;
	REG32RO GPLEV0		: 32;
	REG32RO GPLEV1		: 32;
	RESRV32 RESERVED3	: 32;
	REG32RW GPEDS0		: 32;
	REG32RW GPEDS1		: 32;
	RESRV32 RESERVED4	: 32;
	REG32RW GPREN0		: 32;
	REG32RW GPREN1		: 32;
	RESRV32 RESERVED5	: 32;
	REG32RW GPFEN0		: 32;
	REG32RW GPFEN1		: 32;
	RESRV32 RESERVED6	: 32;
	REG32RW GPHEN0		: 32;
	REG32RW GPHEN1		: 32;
	RESRV32 RESERVED7	: 32;
	REG32RW GPLEN0		: 32;
	REG32RW GPLEN1		: 32;
	RESRV32 RESERVED8	: 32;
	REG32RW GPAREN0		: 32;
	REG32RW GPAREN1		: 32;
	RESRV32 RESERVED9	: 32;
	REG32RW GPAFEN0		: 32;
	REG32RW GPAFEN1		: 32;
	RESRV32 RESERVEDA	: 32;
	REG32RW GPPUD		: 32;
	REG32RW GPPUDCLK0	: 32;
	REG32RW GPPUDCLK1	: 32;
	RESRV32 RESERVEDB	: 32;
	REG32RW TEST		: 32;
};
}




#endif /* IO_MEMORY_GPREGS_HPP_ */