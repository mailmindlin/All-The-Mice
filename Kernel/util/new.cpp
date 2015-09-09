/*
 * new.cpp
 *
 *  Created on: Aug 21, 2015
 *      Author: wfeehery17
 */

#include "new.h"

#include <util/alloc.h>
#include <cstdint>

void* operator new(uint32_t size) {
	return malloc(size);
}
void* operator new[](uint32_t size) {
	return malloc(size);
}
void operator delete(void* block) {
	if(block!=0)
		free(block);
}
void operator delete[](void* block) {
	if(block!=0)
		free(block);
}
