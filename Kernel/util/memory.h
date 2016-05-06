/*
 * memory.h
 * Header for memory.s
 *  Created on: Sep 24, 2015
 *      Author: mailmindlin
 */
#pragma once
#include <util/syscfg.h>
#ifndef UTIL_MEMSET_H_
#define UTIL_MEMSET_H_
#ifndef SIZE_T
#ifdef ARM_ARCH_64
#define SIZE_T unsigned long
#else
#define SIZE_T unsigned
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif
	extern void* memset(void* dest, unsigned int c, SIZE_T count);
	extern void* memcpy(void* dest, const void* src, SIZE_T size);
	extern bool  limstrcpy(char* dest, const char* src, SIZE_T maxSize);
	extern SIZE_T limstrlen(const char* str, SIZE_T maxLen);
#ifdef __cplusplus
}
#endif
#endif /* UTIL_MEMSET_H_ */
