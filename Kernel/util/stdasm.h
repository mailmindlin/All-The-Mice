/*
 * stdasm.h
 *
 *  Created on: Sep 24, 2015
 *      Author: mailmindlin
 */

#ifndef UTIL_STDASM_H_
#define UTIL_STDASM_H_

#include <stddef.h>
#include <stdint.h>

#if (!defined(EXC)) || (!defined(EXT))
#define EXC extern "C"
#define EXT extern "C++"
#endif
namespace ASM {

template<typename T> inline void write(T* ptr, T data);
template<typename T> inline void writeV(T* volatile ptr, T data);
EXC inline void write16(uint32_t addr, uint16_t data);
EXC inline void write32(uint32_t addr, uint32_t data);
template<typename T> inline T read(T* ptr);
template<typename T> inline T readV(T* volatile ptr);
EXC inline uint16_t read16(uint32_t addr);
EXC inline uint32_t read32(uint32_t addr);
EXC inline uint64_t read64(uint32_t reg, uint32_t shift);
EXC inline void delay(int32_t count);

}



#endif /* UTIL_STDASM_H_ */
