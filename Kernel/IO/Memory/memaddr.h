/*
 * MemAddr.h
 * Memory addresses for a bunch of peripherals (so if I get the addresses wrong, I can fix it without
 * changing every reference to these, like if they are different on the RPi2 for something.
 *  Created on: Feb 25, 2015
 *      Author: mailmindlin
 */

#ifndef IO_MEMORY_MEMADDR_H_
#define IO_MEMORY_MEMADDR_H_

#include <stddef.h>

#include "gpregs.hpp"
#include "memtypes.hpp"

namespace MemoryMap {

//Some values from https://github.com/rsta2/circle/blob/master/include/circle/bcm2835.h

#define HRPTR(name) extern "C++" memptr_t name
#define HBCST(name) extern "C++" memconst_t name

#ifndef __RPI_REVISION
	#define __RPI_REVISION 2
#endif

extern "C++" memconst_t BCM_IO_BASE;

extern "C++" memconst_t GPIO_BASE;

extern "C++" const GPREGS *GPIO_REGS;

extern "C++" size_t		BLOCK_SIZE;
HBCST(BSC0_ADDRESS);
HBCST(BSC1_ADDRESS);
HBCST(BSC2_ADDRESS);

//UART0
HBCST(UART0_BASE);
HRPTR(UART0_DR);
HRPTR(UART0_RSRECR);
HRPTR(UART0_FR);
HRPTR(UART0_ILPR);
HRPTR(UART0_IBRD);
HRPTR(UART0_FBRD);
HRPTR(UART0_LCRH);
HRPTR(UART0_CR);
HRPTR(UART0_IFLS);
HRPTR(UART0_IMSC);
HRPTR(UART0_RIS);
HRPTR(UART0_MIS);
HRPTR(UART0_ICR);
HRPTR(UART0_DMACR);
HRPTR(UART0_ITCR);
HRPTR(UART0_ITIP);
HRPTR(UART0_ITOP);
HRPTR(UART0_TDR);

/**
 * System timers
 */
HBCST(SYSTIMER_BASE);
HRPTR(SYSTIMER_CS);
HRPTR(SYSTIMER_CLO);
HRPTR(SYSTIMER_CHI);
HRPTR(SYSTIMER_C0);
HRPTR(SYSTIMER_C1);
HRPTR(SYSTIMER_C2);
HRPTR(SYSTIMER_C3);

/**
 * Platform DMA controller
 */
HBCST(DMA_BASE);


/**
 * Interrupt controller
 */
HBCST(IC_BASE);
HRPTR(IC_IRQ_BASIC_PENDING);
HRPTR(IC_IRQ_PENDING_1);
HRPTR(IC_IRQ_PENDING_2);
HRPTR(IC_FIQ_CONTROL);
HRPTR(IC_ENABLE_IRQS_1);
HRPTR(IC_ENABLE_IRQS_2);
HRPTR(IC_ENABLE_BASIC_IRQS);
HRPTR(IC_DISABLE_IRQS_1);
HRPTR(IC_DISABLE_IRQS_2);
HRPTR(IC_DISABLE_BASIC_IRQS);

/**
 * ARM timer
 */
HBCST(ARMTIMER_BASE);
HRPTR(ARMTIMER_LOAD);
HRPTR(ARMTIMER_VALUE);
HRPTR(ARMTIMER_CTRL);
HRPTR(ARMTIMER_IRQCLR);
HRPTR(ARMTIMER_RAWIRQ);
HRPTR(ARMTIMER_MASKIRQ);
HRPTR(ARMTIMER_RELOAD);
HRPTR(ARMTIMER_PREDIV);
HRPTR(ARMTIMER_CNTR);


//GPU addresses
HBCST(GPU_BASE);
HRPTR(GPU_READ);
HRPTR(GPU_POLL);
HRPTR(GPU_SENDER);
HRPTR(GPU_STATUS);
HRPTR(GPU_CONFIG);
HRPTR(GPU_WRITE);


HBCST(EMMC_BASE);
}
#undef HRPTR
#undef HBCST
#endif /* IO_MEMADDR_HPP_ */
