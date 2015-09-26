/*
 * mmio.c
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#ifndef STDASM_CPP_
#define STDASM_CPP_

#include "stdasm.h"

namespace ASM {
/**
 * Write {data} to location stored in {ptr}
 * @param ptr
 * 			pointer to where to store data
 * @param data
 * 			data to store
 */
template<typename T> inline void write(T* ptr, T data) {
	*ptr = data;
}
/**
 * Write data to address of volatile pointer
 */
template<typename T> inline void writeV(T* volatile ptr, T data) {
	*ptr = data;
}
/**
 * Equivalent of STRH (store half of a word, or 16 bits). This is different from STR,
 * as if you attempted to STR a 16bit variable, it would zero the upper 16 bits to make
 * it a word (remember, ARM is 32 bit).
 */
EXC inline void write16(uint32_t addr, uint16_t data) {
	uint32_t *ptr = (uint32_t*) addr;
	asm volatile("strh %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));
}
/**
 * Equivalent of STR (store a word, or 32 bits).
 */
EXC inline void write32(uint32_t addr, uint32_t data) {
	uint32_t *ptr = (uint32_t*) addr;
	asm volatile("str %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));
}
//TODO finish
//EXC inline void write64(uint32_t addr, uint64_t data) {
//	uint32_t *ptr = (uint32_t*) addr;
//}
/**
 * Read and return data at memory address of {ptr}.
 */
template<typename T> inline T read(T* ptr) {
	return *ptr;
}
/**
 * Read and return data at volatile memory address of {ptr}
 */
template<typename T> inline T readV(T* volatile ptr) {
	return *ptr;
}
/**
 * Equivalent of LDRh (read 1/2 word, or 16 bits). I don't think that it's too different
 * from `read32(addr) & 0xFFFF`, but someone will probably correct me, and I'll probably
 * think that whatever reason that it is is really interesting.
 */
EXC inline uint16_t read16(uint32_t addr) {
	uint32_t *ptr = (uint32_t*) addr;
	uint16_t data;
	asm volatile("ldrh %[data], [%[reg]]" : [data]"=r"(data) : [reg]"r"(ptr));
	return data;
}
/**
 * Equivalent of LDR (read 1 word, or 32 bits).
 */
EXC inline uint32_t read32(uint32_t addr) {
	uint32_t *ptr = (uint32_t*) addr;
	uint32_t data;
	asm volatile("ldr %[data], [%[reg]]" : [data]"=r"(data) : [reg]"r"(ptr));
	return data;
}
/**
 *
 */
EXC inline uint64_t read64(uint32_t reg, uint32_t shift) {
	uint32_t *ptr = (uint32_t*) reg;
	uint32_t *sptr= (uint32_t*) shift;
	uint32_t data0, data1;
#ifdef PURE_LDRD
	asm volatile("ldrd %[data0], %[data1], [%[reg], %[shft]] (!)" : [data0]"=r"(data0), [data1]"=r"(data1) : [reg]"r"(ptr), [shft]"r"(sptr) : );
	return data0 | (((uint64_t) data1) << 32);
#else
	//TODO I think that you have to make sure that data1 is read from a different address from data0
	asm volatile("ldr %[data0], [%[reg], %[shft]]" : [data0]"=r"(data0) : [reg]"r"(ptr), [shft]"r"(sptr) : );
	asm volatile("ldr %[data1], [%[reg], %[shft]]" : [data1]"=r"(data1) : [reg]"r"(ptr), [shft]"r"(sptr) : );
	return data0 | (((uint64_t) data1) << 32);
#endif
}
//macro versions
#define STRH(data,reg) {uint32_t *ptr = (uint32_t*) addr; asm volatile("str %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));}
#define STR(data,reg) {uint32_t *ptr = (uint32_t*) addr; asm volatile("str %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));}
/* Loop <delay> times in a way that the compiler won't optimize away. */
EXC inline void delay(int32_t count) {
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n" : : [count]"r"(count) : "cc");
}
}
#endif
