/**
 * DisplayUtils.h
 *
 *  Created on: Sep 25, 2015
 *      Author: Liam
 */

#ifndef IO_DISPLAY_DISPLAYUTILS_H_
#define IO_DISPLAY_DISPLAYUTILS_H_

#include <stddef.h>
#include <cstdint>
#include <type_traits>

#define COLOR_DEPTH	32		// can be: 8, 16 or 32

// really ((green) & 0x3F) << 5, but to have a 0-31 range for all colors
#define COLOR16(red, green, blue)	  (((red) & 0x1F) << 11 | ((green) & 0x1F) << 6 | ((blue) & 0x1F))

#define COLOR32(red, green, blue, alpha)  (((red) & 0xFF) | ((green) & 0xFF) << 8  | ((blue) & 0xFF) << 16 | ((alpha) & 0xFF) << 24)

#define COLOR_BLACK	0

#if COLOR_DEPTH == 8
	#pragma message ("Using color depth of 8")
	typedef uint8_t TScreenColor;

	#define COLOR_NORMAL16			COLOR16 (31, 31, 31)
	#define COLOR_HIGH16			COLOR16 (31, 0, 0)
	#define COLOR_HALF16			COLOR16 (0, 0, 31)

	#define COLOR_NORMAL			1
	#define COLOR_HIGH				2
	#define COLOR_HALF				3
#elif COLOR_DEPTH == 16
	#pragma message ("Using color depth of 16")
	#define COLOR_RGB(red, green, blue) COLOR16(red, green, blue)
	typedef uint16_t TScreenColor;

	#define COLOR_NORMAL			COLOR16 (31, 31, 31)
	#define COLOR_HIGH				COLOR16 (31, 0, 0)
	#define COLOR_HALF				COLOR16 (0, 0, 31)
#elif COLOR_DEPTH == 32
	#pragma message ("Using color depth of 32")
	#define COLOR_RGB(red, green, blue, alpha) COLOR32(red, green, blue, alpha)
	typedef uint32_t TScreenColor;

	#define COLOR_NORMAL			COLOR32 (255, 255, 255, 255)
	#define COLOR_HIGH				COLOR32 (255, 0, 0, 255)
	#define COLOR_HALF				COLOR32 (0, 0, 255, 255)
#else
	#error COLOR_DEPTH must be 8, 16 or 32
#endif



#endif /* IO_DISPLAY_DISPLAYUTILS_H_ */
