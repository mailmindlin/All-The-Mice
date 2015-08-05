.title "Bitutils"
.sbttl "Macros for bitwise manipulation"
.macro
$label bitOn $addr, $mask
	ldr r0, $addr
	orr r0,r0,$mask
.mend