// --------------UART CONFIGURATION------------------@
.func _initUART
.globl _initUART
_initUART:
	push {
	// Enable UART
	ldr r1, =0x53FBC080
	mov r0, #1
	str r0, [r1]
	// Set hardware flow control, data format and enable trans/receiver
	ldr r0, =0x2127
	str r0, [r1, #4]!
	// Set UCR3[RXDMUXSEL] = 1
	ldr r0, =0x0704
	str r0, [r1, #4]!
	// Set CTS trigger level to 31
	ldr r0, =0x7C00
	str r0, [r1, #4]!
	// Set internal clock divider = 5
	ldr r0, =0x089E
	str r0, [r1, #4]!
	// Set baud rate to 921.6kbps
	ldr r0, =0x08FF
	str r0, [r1, #20]!
	ldr r0, =0x0C34
	str r0, [r1, #4]
	BX lr
.endfunc
// ----Write to UART
.func _writeUART
.globl _writeUART
_writeUART:
	push {r4-r6}
	ldr r3, =0x53FBC094
	ldr r5, =0x53FBC040
	mov r0, r2
	mov r0, #(1<<13)
	writeLoop:
		cmp r2, #0
		beq doneWriting
		// Wait for the transmission queue be ready
		transmitterLoop:
			ldr r4, [r3]
			and r4, r4, r0
			cmp r4, #0
			beq transmitterLoop
		ldrb r6, [r1], #1
		strb r6, [r5]
		sub r2, r2, #1
		b writeLoop
	doneWriting:
		pop {r4-r6}
	BX lr
.ltorg
.end
