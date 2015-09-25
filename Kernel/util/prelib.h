/*
 * prelib.h
 *
 * A colection of all the stuff that you have to fix before importing anything from the
 * stl.
 *
 *  Created on: Sep 24, 2015
 *      Author: mailmindlin
 */

#ifndef UTIL_PRELIB_H_
#define UTIL_PRELIB_H_

#if defined(__REALCOMP__) && not defined(__GXX_EXPERIMENTAL_CXX0X__)
#define __GXX_EXPERIMENTAL_CXX0X__
//because for some reason Yagarto has a problem with the following types not being defined.
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
#endif

#endif /* UTIL_PRELIB_H_ */
