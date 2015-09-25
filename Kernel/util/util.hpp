/*
 * util.hpp
 *
 *  Created on: Aug 6, 2015
 *      Author: mailmindlin
 */

#ifndef UTIL_UTIL_HPP_
#define UTIL_UTIL_HPP_

#define PACKED		__attribute__ ((packed))
#define	ALIGN(n)	__attribute__ ((aligned (n)))
#define NOOPT		__attribute__ ((optimize (0)))
#define MAXOPT		__attribute__ ((optimize (3)))

// big endian (to be used for constants only)
#define BE(value)	((((value) & 0xFF00) >> 8) | (((value) & 0x00FF) << 8))


#endif /* UTIL_UTIL_HPP_ */
