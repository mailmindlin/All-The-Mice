/*
 * mmio.c
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef STDASM_CPP_
#define STDASM_CPP_
#include <stddef.h>
#include <stdint.h>
#if (!defined(EXC)) || (!defined(EXT))
#define EXC extern "C"
#define EXT extern "C++"
#endif
namespace ASM {
template<typename T> inline void write(T* ptr, T data) {
	*ptr = data;
}
template<typename T> inline void writeV(T* volatile ptr, T data) {
	*ptr = data;
}
EXC inline void write16(uint32_t addr, uint16_t data) {
	uint32_t *ptr = (uint32_t*) addr;
	asm volatile("strh %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));
}
EXC inline void write32(uint32_t addr, uint32_t data) {
	uint32_t *ptr = (uint32_t*) addr;
	asm volatile("str %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));
}
//TODO finish
//EXC inline void write64(uint32_t addr, uint64_t data) {
//	uint32_t *ptr = (uint32_t*) addr;
//}
template<typename T> inline T read(T* ptr) {
	return *ptr;
}
template<typename T> inline T readV(T* volatile ptr) {
	return *ptr;
}
EXC inline uint16_t read16(uint32_t addr) {
	uint32_t *ptr = (uint32_t*) addr;
	uint16_t data;
	asm volatile("ldrh %[data], [%[reg]]" : [data]"=r"(data) : [reg]"r"(ptr));
	return data;
}
EXC inline uint32_t read32(uint32_t addr) {
	uint32_t *ptr = (uint32_t*) addr;
	uint32_t data;
	asm volatile("ldr %[data], [%[reg]]" : [data]"=r"(data) : [reg]"r"(ptr));
	return data;
}
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
