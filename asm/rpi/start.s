// To keep this in the first portion of the binary.
.section ".text.boot"
.title "MMOS Bootloader"
.sbttl "Custom Raspberry Pi OS"
// Make _start global.
.globl _start
.extern kernel_main
.extern kernel_shutdown
.extern _exit
 
// Entry point for the kernel.
// r15 -> should begin execution at 0x8000.
// r0 -> 0x00000000
// r1 -> 0x00000C42
// r2 -> 0x00000100 - start of ATAGS
// preserve these registers as argument for kernel_main
.org 0x0
_start:
	// Setup the stack.
//	blx _initScheduler
// 	blx _initVectors
	mov sp, #0x8000
 
	// Clear out bss.
	ldr r4, =__bss_start
	ldr r9, =__bss_end
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	b       2f
 
1:
	// store multiple at r4.
	stmia r4!, {r5-r8}
 
	// If we are still below bss_end, loop.
2:
	cmp r4, r9
	blo 1b
	
	//enable FPU (from http://www.raspberrypi.org/forums/viewtopic.php?f=72&t=11183)
	mrc p15, 0, r0, c1, c0, 2
	orr r0, r0, #0xF00000            /* single & double precision */
	mcr p15, 0, r0, c1, c0, 2
	mov r0, #0x40000000
	fmxr fpexc,r0
 
	// Call kernel_main
	// (setup args)
	mov r0, #0x00000000
// 	mov r1, #0x00000C42
	mov r2, #0x00000100//start of ATAGs
	ldr r3, =kernel_main
	blx r3
	ldr r3, =kernel_shutdown
	blx r3
	ldr r3, =_exit
	blx r3
	//now call halt, because we are done.
.globl halt
halt:
	wfe
	b halt
.ltorg
.end
