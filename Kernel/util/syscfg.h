/*
 * syscfg.h
 * Contains information about the capabilities of the pi.
 *
 *  Created on: Aug 6, 2015
 *      Author: mailmindlin
 */

#ifndef UTIL_SYSCFG_H_
#define UTIL_SYSCFG_H_

// memory addresses and sizes
#define KILOBYTE		0x400
#define MEGABYTE		0x100000
#define GIGABYTE		0x40000000

#define PI_MODEL_A		0
#define PI_MODEL_B		1
#define PI_MODEL_AP		2//A+
#define PI_MODEL_BP		3//B+
#define	PI_MODEL_B2		4
#define	PI_MODEL_ALPHA	5
#define	PI_MODEL_CM		6
#define	PI_MODEL_B3		8
#define	PI_MODEL_ZERO	9

//check that __RPI_MODEL is defined
#ifndef __RPI_MODEL
#warning __RPI_MODEL not set. Defaulting to PI_MODEL_B2
#define __RPI_MODEL PI_MODEL_B2
#endif

//Different Raspberry Pi's have different amounts of RAM
//TODO fix for more models
#if (__RPI_MODEL == PI_MODEL_A) || (__RPI_MODEL == PI_MODEL_AP) || (__RPI_MODEL == PI_MODEL_ZERO)
	#define MEM_SIZE		(256 * MEGABYTE)			// default size
#elif (__RPI_MODEL == PI_MODEL_B) || (__RPI_MODEL == PI_MODEL_BP) || (__RPI_MODEL == PI_MODEL_CM)
	#define MEM_SIZE		(512 * MEGABYTE)
#elif (__RPI_MODEL == PI_MODEL_B2) || (__RPI_MODEL == PI_MODEL_B3)
	#define MEM_SIZE		(1 * GIGABYTE)
#else
	#warning Unknown amount of RAM. Defaulting to 256M.
	#define MEM_SIZE		(256 * MEGABYTE)
#endif

#if __RPI_MODEL == PI_MODEL_A
	#define RPI_BUILTIN_USB		1
	#define RPI_BUILTIN_HDMI
	#define RPI_BUILTIN_SVIDEO
	#define RPI_BUILTIN_AUDIO
	#define RPI_BUILTIN_GPIO_SIZE 26
#elif __RPI_MODEL == PI_MODEL_ZERO
	#define RPI_BUILTIN_HDMI_MINI
	#define RPI_BUILTIN_USB_MINI
	#define RPI_BUILTIN_GPIO_SIZE 40
#elif __RPI_MODEL == PI_MODEL_B
	#define RPI_BUILTIN_ETHERNET
	#define RPI_BUILTIN_USB		2
	#define RPI_BUILTIN_HDMI
	#define RPI_BUILTIN_SVIDEO
	#define RPI_BUILTIN_AUDIO
	#define RPI_BUILTIN_GPIO_SIZE 26
#elif __RPI_MODEL == PI_MODEL_AP
	#define RPI_BUILTIN_USB		1
	#define RPI_BUILTIN_HDMI
	#define RPI_BUILTIN_AUDIO
	#define RPI_BUILTIN_GPIO_SIZE 40
#elif __RPI_MODEL == PI_MODEL_BP
	#define RPI_BUILTIN_ETHERNET
	#define RPI_BUILTIN_USB		4
	#define RPI_BUILTIN_HDMI
	#define RPI_BUILTIN_AUDIO
	#define RPI_BUILTIN_GPIO_SIZE 40
#elif __RPI_MODEL == PI_MODEL_B2
	#define RPI_BUILTIN_ETHERNET
	#define RPI_BUILTIN_USB		4
	#define RPI_BUILTIN_HDMI
	#define RPI_BUILTIN_AUDIO
	#define RPI_BUILTIN_GPIO_SIZE 40
#elif __RPI_MODEL == PI_MODEL_CM
	#define RPI_BUILTIN_GPIO_SIZE 0
	//TODO finish
#elif __RPI_MODEL == PI_MODEL_B3
	#define RPI_BUILTIN_ETHERNET
	#define RPI_BUILTIN_USB		4
	#define RPI_BUILTIN_HDMI
	#define RPI_BUILTIN_AUDIO
	#define RPI_BUILTIN_BLUETOOTH
	#define RPI_BUILTIN_BLE
	#define RPI_BUILTIN_WIFI
	#define RPI_BUILTIN_GPIO_SIZE 40
#endif

#define GPU_MEM_SIZE		(64 * MEGABYTE)				// set in config.txt
#define ARM_MEM_SIZE		(MEM_SIZE - GPU_MEM_SIZE)	// normally overwritten

#define PAGE_SIZE				4 * KILOBYTE				// page size used by us

#define KERNEL_MAX_SIZE			(2 * MEGABYTE)				// all sizes must be a multiple of 16K
#define KERNEL_STACK_SIZE		0x20000
#define EXCEPTION_STACK_SIZE	0x8000
#define PAGE_TABLE1_SIZE		0x4000
#define PAGE_RESERVE			(4 * MEGABYTE)

#define MEM_KERNEL_START		0x8000
#define MEM_KERNEL_END			(MEM_KERNEL_START + KERNEL_MAX_SIZE)
#define MEM_KERNEL_STACK		(MEM_KERNEL_END + KERNEL_STACK_SIZE)		// expands down

#ifndef __RPI_REVISION
	#warning __RPI_REVISION not set.
	#if (__RPI_MODEL == PI_MODEL_A) || (__RPI_MODEL == PI_MODEL_AP) || (__RPI_MODEL == PI_MODEL_B) || (__RPI_MODEL == PI_MODEL_BP) || (__RPI_MODEL == PI_MODEL_CM)
		#warning I'm guessing that __RPI_REVISION is 1
		#define __RPI_REVISION	1
	#elif (__RPI_MODEL == PI_MODEL_B2)
		#warning I'm guessing that __RPI_REVISION is 2
		#define __RPI_REVISION	2
	#elif (__RPI_MODEL == PI_MODEL_B3)
		#warning I'm guessing that __RPI_REVISION is 3
		#define __RPI_REVISION	3
	#else
		#warning Defaulting __RPI_REVISION to 2
		#define __RPI_REVISION	2//pretty safe
	#endif
#endif

#if __RPI_REVISION == 1
	#define CORES				1
	#define MEM_ABORT_STACK		(MEM_KERNEL_STACK + EXCEPTION_STACK_SIZE)	// expands down
	#define MEM_IRQ_STACK		(MEM_ABORT_STACK + EXCEPTION_STACK_SIZE)	// expands down
	#define MEM_PAGE_TABLE1		MEM_IRQ_STACK								// must be 16K aligned
	#define ARM_STRICT_ALIGNMENT
	#define GPU_L2_CACHE_ENABLED
	#define BCM_BASE			0x20000000
#elif __RPI_REVISION == 2
	#define ARM_ALLOW_MULTI_CORE					// slower on single core if defined
	#define CORES				4					// must be a power of 2
	#define MEM_ABORT_STACK		(MEM_KERNEL_STACK + KERNEL_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
	#define MEM_IRQ_STACK		(MEM_ABORT_STACK + EXCEPTION_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
	#define MEM_PAGE_TABLE1		(MEM_IRQ_STACK + EXCEPTION_STACK_SIZE * (CORES-1))
	#define BCM_BASE			0x3F000000
#elif __RPI_REVISION == 3
	#define ARM_ALLOW_MULTI_CORE					// slower on single core if defined
	#define CORES				4					// must be a power of 2
	#define ARM_ARCH_64
	#define MEM_ABORT_STACK		(MEM_KERNEL_STACK + KERNEL_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
	#define MEM_IRQ_STACK		(MEM_ABORT_STACK + EXCEPTION_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
	#define MEM_PAGE_TABLE1		(MEM_IRQ_STACK + EXCEPTION_STACK_SIZE * (CORES-1))
	#define BCM_BASE			0x3F000000
#else
	#error unknown value of __RPI_REVISION
#endif

#define MEM_HEAP_START		0x400000

#define KERNEL_TIMERS		20

// default leopard map (enable only one)
#define KEYMAP_US			0
#define KEYMAP_UK			1
#define KEYMAP_DE			2
#define KEYMAP_ES			3
#ifndef DEFAULT_KEYMAP
	#define DEFAULT_KEYMAP		KEYMAP_US
#endif
#endif /* UTIL_SYSCFG_H_ */
