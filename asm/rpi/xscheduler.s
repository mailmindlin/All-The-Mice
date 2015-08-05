//Configurable STACK values for each ARM core operation mode
.set USR_STACK, 0x11000//user mode			
.set SVC_STACK, 0x10800
.set ABT_STACK, 0x10800
.set FIQ_STACK, 0x07c00
.set IRQ_STACK, 0x07800
.set SYS_STACK, 0x07400
.set UND_STACK, 0x07000
//mode values
.set USR_MODE, 0x10//User mode:			Usual ARM program execution state, and is used for executing most application programs.
.set FIQ_MODE, 0xD1//FIQ mode			Supports a data transfer or channel process.
.set IRQ_MODE, 0xD2//IRQ mode			For general-purpose interrupt handling.
.set SVC_MODE, 0xD3//supervisor mode	Protected mode for the operating system.
.set ABT_MODE, 0x17//Abort mode			After a data or instruction Prefetch Abort.
.set UND_MODE, 0x1B//Undefined mode		For undefined operations
//You can only enter System mode from another privileged mode by modifying the mode bit of the Current Program Status Register (CPSR).
.set SYS_MODE, 0xDF//System mode		Privileged user mode for the operating system.

.set TIMER0_ADDR, 0x101E2000

// Initialize scheduler
//void _initScheduler(void);
.globl _initScheduler
.func _initScheduler
_initScheduler:
//Ref: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0243c/ch04s05s02.html
	push {lr}
	// Initialize Stack Points of All Modes
	// (already should be in SVC mode)
	mov sp, #SVC_STACK 
	msr CPSR_c, #0xDF	// Enter system mode, FIQ/IRQ disabled
	mov sp, #USR_STACK
	msr CPSR_c, #0xD1	// Enter FIQ mode, FIQ/IRQ disabled
	mov sp, #FIQ_STACK
	msr CPSR_c, #0xD2	// Enter IRQ mode, FIQ/IRQ disabled
	mov sp, #IRQ_STACK
	msr CPSR_c, #0xD7	// Enter abort mode, FIQ/IRQ disabled
	mov sp, #ABT_STACK
	msr CPSR_c, #0xDB	// Enter undefined mode, FIQ/IRQ disabled
	mov sp, #UND_STACK
	
	//Setup timer
	TIMER .req r4
	ldr TIMER, =TIMER0_ADDR
	//disable timer, free running mode, enable interrupt, prescale /1, 32 bit, one shot
	AND TIMER,TIMER, #0b00110011
	ORR TIMER,TIMER, #0b00100011
	//return
	pop {pc}
	.unreq TIMER
.endfunc

//void _beginScheduler(void);
.globl _beginScheduler
.func _beginScheduler
_beginScheduler:
	push {lr}
	ldr r0, =TIMER0_ADDR
	//ORR help: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0489i/CIHJCJDD.html, http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.kui0100a/armasm_cihdafai.htm
	orr r0, r0, #0b10000000
	pop {pc}
.endfunc

//void _stopScheduler(void);
.globl _stopScheduler
.func _stopScheduler
_stopScheduler:
	push {lr}
	ldr r0, =TIMER0_ADDR
	and r0, r0, #0b01111111
	pop {pc}
.endfunc

.ltorg
.end
