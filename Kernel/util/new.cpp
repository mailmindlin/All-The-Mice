/*
 * new.cpp
 *
 *  Created on: Aug 21, 2015
 *      Author: mailmindlin
 */

#include "new.h"


void* operator new(size_t size) {
	return malloc(size);
}
void* operator new[](size_t size) {
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
