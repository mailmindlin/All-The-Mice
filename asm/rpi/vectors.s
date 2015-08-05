.title "Vectors"
//From https://github.com/dwelch67/raspberrypi/blob/master/blinker05/vectors.s
//Modified by mailmindlin
//.extern undefined_handler
//.extern swi_handler
//.extern prefetch_handler
//.extern data_handler
//.extern unused_handler
//.extern irq_handler
//.extern fiq_handler
.extern IRQHandler

.func _initVectors
.globl _initVectors
_initVectors:
	push {lr}
    ldr pc,_asm_reset_handler
    ldr pc,_asm_undefined_handler
    ldr pc,_asm_swi_handler
    ldr pc,_asm_prefetch_handler
    ldr pc,_asm_data_handler
    ldr pc,_asm_unused_handler
    ldr pc,_asm_irq_handler
    ldr pc,_asm_fiq_handler
    pop {pc}
.endfunc
_asm_reset_handler:      .word _reset_handler
//_asm_undefined_handler:  .word undefined_handler
_asm_undefined_handler:
	push {fp, lr}
	add	fp, sp, #0
	ldr r0, =undefined_handler
	ldr r0, [r0]
	bl cfptr
	sub	sp, fp, #4
	pop	{fp, lr}
	bx	lr

_asm_swi_handler:		.word swi_handler
_asm_prefetch_handler:	.word prefetch_handler
_asm_data_handler:		.word data_handler
_asm_unused_handler:	.word unused_handler
_asm_irq_handler:		.word _irq_handler
_asm_fiq_handler:		.word fiq_handler

.globl _reset_handler
.func _reset_handler
_reset_handler:
    mov r0,#0x8000
    mov r1,#0x0000
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}


    //@ (PSR_IRQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD2
    msr cpsr_c,r0
    mov sp,#0x8000

    //@ (PSR_FIQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD1
    msr cpsr_c,r0
    mov sp,#0x4000

    //@ (PSR_SVC_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD3
    msr cpsr_c,r0
    mov sp,#0x8000000

    //@ SVC MODE, IRQ ENABLED, FIQ DIS
    //@mov r0,#0x53
    //@msr cpsr_c, r0
	//return
	mov pc,lr
.endfunc

.globl _enable_irq
.func _enable_irq
_enable_irq:
    mrs r0,cpsr
    bic r0,r0,#0x80
    msr cpsr_c,r0
    bx lr
.endfunc
/**
 * Default entry for IRQ events
 * Will then call irq_handler
 * void _irq_handler(void);
 */
.globl _irq_handler
.func _irq_handler
_irq_handler:
	SUB         lr, lr, #4
    SRSDB       sp!,#31          // Save LR_irq and SPSR_irq to System mode stack
    CPS #031                     // Switch to System mode
    PUSH        {R0-R3,R12}      // Store other AAPCS registers
    AND         R1, sp, #4
    SUB         sp, sp, R1
    PUSH        {R1, lr}
//    BL          identify_and_clear_source
    CPSIE       i                // Enable IRQ
    BL          IRQHandler
    CPSID i                      // Disable IRQ
    POP         {R1,lr}
    ADD         sp, sp, R1
    POP         {R0-R3, R12}     // Restore registers
    RFEIA       sp!              // Return using RFE from System mode stack
// _irq_handler:
//    push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
//    bl irq_handler
//    pop  {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
//    subs pc,lr,#4
.endfunc

//@-------------------------------------------------------------------------
//@-------------------------------------------------------------------------

//@-------------------------------------------------------------------------
//@
//@ Copyright (c) 2012 David Welch dwelch@dwelch.com
//@
//@ Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//@
//@ The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//@
//@ THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//@
//@-------------------------------------------------------------------------
.ltorg
.end
