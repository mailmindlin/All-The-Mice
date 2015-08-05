//c definition: uint8_t getMode();
.globl getCPSRNum
.func getCPSRNum
getCPSRNum:
	push {fp, lr}
	mrs R0, CPSR
	pop	{fp, lr}
	bx lr
.endfunc
.globl setCPSRNum
.func setCPSRNum
setCPSRNum:
	push {fp, lr}
	msr CPSR, R0
	pop	{fp, lr}
	bx lr
.endfunc
.ltorg
.end
