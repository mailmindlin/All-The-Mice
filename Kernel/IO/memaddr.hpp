/*
 * MemAddr.h
 * Memory addresses for a bunch of peripherals (so if I get the addresses wrong, I can fix it without
 * changing every reference to these, like if they are different on the RPi2 for something.
 *  Created on: Feb 25, 2015
 *      Author: mailmindlin
 */

#ifndef IO_MEMADDR_HPP_
#define IO_MEMADDR_HPP_

namespace MemoryMap {
typedef const uint32_t memconst_t;
typedef volatile uint32_t* memptr_t;

memconst_t	BCM2708_PERI_BASE	= 0x20000000;
memconst_t	GPIO_ADDRESS		= (BCM2708_PERI_BASE + 0x00200000); //0x20200000

size_t		BLOCK_SIZE			= (4*1024);
memconst_t	BSC0_ADDRESS		= (BCM2708_PERI_BASE + 0x00205000); //0x20205000
memconst_t	BSC1_ADDRESS		= (BCM2708_PERI_BASE + 0x00804000); //0x20804000
memconst_t	BSC2_ADDRESS		= (BCM2708_PERI_BASE + 0x00805000); //0x20805000

memconst_t	GPU_BASE			= (BCM2708_PERI_BASE + 0x0000B880); //0x20
memptr_t	GPU_READ			= (memptr_t)(GPU_BASE + 0x00); //0x20
memptr_t	GPU_POLL			= (memptr_t)(GPU_BASE + 0x10); //0x20
memptr_t	GPU_SENDER			= (memptr_t)(GPU_BASE + 0x14); //0x20
memptr_t	GPU_STATUS			= (memptr_t)(GPU_BASE + 0x18); //0x20
memptr_t	GPU_CONFIG			= (memptr_t)(GPU_BASE + 0x1C); //0x20
memptr_t	GPU_WRITE			= (memptr_t)(GPU_BASE + 0x20); //0x20

memconst_t	UART0_BASE			= (BCM2708_PERI_BASE + 0x00201000);
memptr_t	UART0_DR			= (memptr_t)(UART0_BASE + 0x00);
memptr_t	UART0_RSRECR		= (memptr_t)(UART0_BASE + 0x04);
memptr_t	UART0_FR			= (memptr_t)(UART0_BASE + 0x18);
memptr_t	UART0_ILPR			= (memptr_t)(UART0_BASE + 0x20);
memptr_t	UART0_IBRD			= (memptr_t)(UART0_BASE + 0x24);
memptr_t	UART0_FBRD			= (memptr_t)(UART0_BASE + 0x28);
memptr_t	UART0_LCRH			= (memptr_t)(UART0_BASE + 0x2C);
memptr_t	UART0_CR			= (memptr_t)(UART0_BASE + 0x30);
memptr_t	UART0_IFLS			= (memptr_t)(UART0_BASE + 0x34);
memptr_t	UART0_IMSC			= (memptr_t)(UART0_BASE + 0x38);
memptr_t	UART0_RIS			= (memptr_t)(UART0_BASE + 0x3C);
memptr_t	UART0_MIS			= (memptr_t)(UART0_BASE + 0x40);
memptr_t	UART0_ICR			= (memptr_t)(UART0_BASE + 0x44);
memptr_t	UART0_DMACR			= (memptr_t)(UART0_BASE + 0x48);
memptr_t	UART0_ITCR			= (memptr_t)(UART0_BASE + 0x80);
memptr_t	UART0_ITIP			= (memptr_t)(UART0_BASE + 0x84);
memptr_t	UART0_ITOP			= (memptr_t)(UART0_BASE + 0x88);
memptr_t	UART0_TDR			= (memptr_t)(UART0_BASE + 0x8C);

memconst_t	EMMC_BASE			= (BCM2708_PERI_BASE + 0x00300000);
}
#endif /* IO_MEMADDR_HPP_ */
