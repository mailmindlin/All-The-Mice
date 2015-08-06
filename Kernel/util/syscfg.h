/*
 * syscfg.h
 *
 *  Created on: Aug 6, 2015
 *      Author: wfeehery17
 */

#ifndef UTIL_SYSCFG_H_
#define UTIL_SYSCFG_H_

// memory addresses and sizes
#define KILOBYTE		0x400
#define MEGABYTE		0x100000
#define GIGABYTE		0x40000000

#define MODEL_A1		0
#define MODEL_A1P		1//A+
#define MODEL_B1		2
#define MODEL_B1P		3//B+
#define MODEL_B2		4
#define MODEL_CM		5

//Different Raspberry Pi's have different amounts of RAM
#if (__RPI_MODEL == MODEL_A1) || (__RPI_MODEL == MODEL_A1P)
	#define MEM_SIZE		(256 * MEGABYTE)		// default size
#elif (__RPI_MODEL == MODEL_B1) || (__RPI_MODEL == MODEL_B1P) || (__RPI_MODEL == MODEL_CM)
	#define MEM_SIZE		(512 * MEGABYTE)
#elif (__RPI_MODEL == MODEL_B2)
	#define MEM_SIZE		(1 * GIGABYTE)
#endif

#define GPU_MEM_SIZE		(64 * MEGABYTE)			// set in config.txt
#define ARM_MEM_SIZE		(MEM_SIZE - GPU_MEM_SIZE)	// normally overwritten

#define PAGE_SIZE		4096				// page size used by us

#define KERNEL_MAX_SIZE		(2 * MEGABYTE)			// all sizes must be a multiple of 16K
#define KERNEL_STACK_SIZE	0x20000
#define EXCEPTION_STACK_SIZE	0x8000
#define PAGE_TABLE1_SIZE	0x4000
#define PAGE_RESERVE		(4 * MEGABYTE)

#define MEM_KERNEL_START	0x8000
#define MEM_KERNEL_END		(MEM_KERNEL_START + KERNEL_MAX_SIZE)
#define MEM_KERNEL_STACK	(MEM_KERNEL_END + KERNEL_STACK_SIZE)		// expands down

#if __RPI_REVISION == 1
	#define CORES				1
	#define MEM_ABORT_STACK		(MEM_KERNEL_STACK + EXCEPTION_STACK_SIZE)	// expands down
	#define MEM_IRQ_STACK		(MEM_ABORT_STACK + EXCEPTION_STACK_SIZE)	// expands down
	#define MEM_PAGE_TABLE1		MEM_IRQ_STACK				// must be 16K aligned
	#define ARM_STRICT_ALIGNMENT
	#define GPU_L2_CACHE_ENABLED
#else
	#define ARM_ALLOW_MULTI_CORE	// slower on single core if defined
	#define CORES				4					// must be a power of 2
	#define MEM_ABORT_STACK		(MEM_KERNEL_STACK + KERNEL_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
	#define MEM_IRQ_STACK		(MEM_ABORT_STACK + EXCEPTION_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
	#define MEM_PAGE_TABLE1		(MEM_IRQ_STACK + EXCEPTION_STACK_SIZE * (CORES-1))
#endif

#define MEM_HEAP_START		0x400000

#define KERNEL_TIMERS		20

// default leopard map (enable only one)
#define KEYMAP_US			0
#define KEYMAP_UK			1
#define KEYMAP_DE			2
#define KEYMAP_ES			3
#define DEFAULT_KEYMAP		KEYMAP_US

#endif /* UTIL_SYSCFG_H_ */
