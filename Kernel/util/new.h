/*
 * new.h
 * Sets up the
 *  Created on: Aug 21, 2015
 *      Author: mailmindlin
 */

#ifndef UTIL_NEW_H_
#define UTIL_NEW_H_

#include <cstdint>

void* operator new(uint32_t size);
void* operator new[](uint32_t size);
void operator delete(void* block);
void operator delete[](void* block);
#endif /* UTIL_NEW_H_ */
