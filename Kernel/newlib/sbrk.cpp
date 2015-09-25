/*
 * sbrk.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: mailmindlin
 */
#ifndef NEWLIB_SBRK_CPP_
#define NEWLIB_SBRK_CPP_
#include <stddef.h>
#ifndef NEWLIB_NEWLIB_H_
#include "newlib.h"
#endif
/* Start of the heap.  */
extern const char _HEAP_START __attribute__((section(".heap")));
/* End of the heap (maximum value of heap_ptr).  */
extern const char _HEAP_END __attribute__((section(".heap")));
/**
 * Extend heap space by size bytes.
 * Return start of new space allocated, or -1 for errors
 * Error cases:
 * 1. Allocation is not within heap range
 */
void * _sbrk(ptrdiff_t size) {
	/*
	 * The following two memory locations should be defined in the linker script file
	 */
	static const char * heap_ptr; /* pointer to head of heap */
	const char * old_heap_ptr;
	static unsigned char init_sbrk = 0;

	/* heap_ptr is initialized to HEAP_START */
	if (init_sbrk == 0) {
		heap_ptr = &_HEAP_START;
		init_sbrk = 1;
	}

	old_heap_ptr = heap_ptr;

	if ((heap_ptr + size) > &_HEAP_END) {
		/* top of heap is bigger than _HEAP_MAX */
		errno = ENOMEM;
		return (void *) -1;
	}

	/* success: update heap_ptr and return previous value */
	heap_ptr += size;
	return (void *) old_heap_ptr;
}
#endif
