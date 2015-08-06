/*
 * synchronize.h
 *
 *  Created on: Aug 6, 2015
 *      Author: wfeehery17
 */

#ifndef UTIL_SYNCHRONIZE_H_
#define UTIL_SYNCHRONIZE_H_
#include "syscfg.h"
#include "util.hpp"
#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif
//
// Interrupt control
//
#define	EnableInterrupts()	asm volatile ("cpsie i")
#define	DisableInterrupts()	asm volatile ("cpsid i")

void EnterCritical (void);
void LeaveCritical (void);
#if __RPI_REVISION == 1
	//
	// Cache control
	//
	#define InvalidateInstructionCache()	asm volatile ("mcr p15, 0, %0, c7, c5,  0" : : "r" (0) : "memory")
	#define FlushPrefetchBuffer()		asm volatile ("mcr p15, 0, %0, c7, c5,  4" : : "r" (0) : "memory")
	#define FlushBranchTargetCache()	asm volatile ("mcr p15, 0, %0, c7, c5,  6" : : "r" (0) : "memory")
	#define InvalidateDataCache()		asm volatile ("mcr p15, 0, %0, c7, c6,  0" : : "r" (0) : "memory")
	#define CleanDataCache()			asm volatile ("mcr p15, 0, %0, c7, c10, 0" : : "r" (0) : "memory")

	//
	// Barriers
	//
	#define DataSyncBarrier()			asm volatile ("mcr p15, 0, %0, c7, c10, 4" : : "r" (0) : "memory")
	#define DataMemBarrier() 			asm volatile ("mcr p15, 0, %0, c7, c10, 5" : : "r" (0) : "memory")

	#define InstructionSyncBarrier()	FlushPrefetchBuffer()
	#define InstructionMemBarrier()		FlushPrefetchBuffer()

#else
	//
	// Cache control
	//
	#define InvalidateInstructionCache()	asm volatile ("mcr p15, 0, %0, c7, c5,  0" : : "r" (0) : "memory")
	#define FlushPrefetchBuffer()			asm volatile ("isb" ::: "memory")
	#define FlushBranchTargetCache()		asm volatile ("mcr p15, 0, %0, c7, c5,  6" : : "r" (0) : "memory")

	void InvalidateDataCache (void) MAXOPT;
	void InvalidateDataCacheL1Only (void) MAXOPT;
	void CleanDataCache (void) MAXOPT;

	void InvalidateDataCacheRange (uint32_t nAddress, uint32_t nLength) MAXOPT;
	void CleanDataCacheRange (uint32_t nAddress, uint32_t nLength) MAXOPT;
	void CleanAndInvalidateDataCacheRange (uint32_t nAddress, uint32_t nLength) MAXOPT;

	//
	// Barriers
	//
	#define DataSyncBarrier()				asm volatile ("dsb" ::: "memory")
	#define DataMemBarrier()				asm volatile ("dmb" ::: "memory")

	#define InstructionSyncBarrier()		asm volatile ("isb" ::: "memory")
	#define InstructionMemBarrier()			asm volatile ("isb" ::: "memory")

#endif

#define CompilerBarrier()	asm volatile ("" ::: "memory")

#ifdef __cplusplus
}
#endif

#endif /* UTIL_SYNCHRONIZE_H_ */
