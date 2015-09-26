/*
 * DisplayUtils.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 *
 * Provides many helpful functions involving RGB colors of different bitdepths, to make life easier
 */

#ifndef IO_DISPLAY_DISPLAYUTILS_CPP_
#define IO_DISPLAY_DISPLAYUTILS_CPP_

#include "DisplayUtils.h"

static const char* hexDigits = "0123456789ABCDEF";
void toHexString(char* str, size_t offset, size_t digits, uint64_t num) {
	char* pos = str + digits + offset;
	for (unsigned int i = 0; i < digits; i++) {
		*(--pos) = hexDigits[(num >> (i * 4)) & 0xF];
	}
}
#include <cmath>
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)
#pragma message(VAR_NAME_VALUE(M_PI))
template <typename T> inline constexpr
int signum(T x, std::false_type is_signed) {
    return T(0) < x;
}

template <typename T> inline constexpr
int signum(T x, std::true_type is_signed) {
    return (T(0) < x) - (x < T(0));
}

template <typename T> inline constexpr
int signum(T x) {
    return signum(x, std::is_signed<T>());
}

#endif /* IO_DISPLAY_DISPLAYUTILS_CPP_ */
