/*
 * FramebufferDescription.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_DISPLAY_FRAMEBUFFERDESCRIPTION_HPP_
#define IO_DISPLAY_FRAMEBUFFERDESCRIPTION_HPP_

#include <cstdint>

namespace Peripherals {
namespace Display {
struct FrameBufferDescription {
	uint32_t width;		//physical width
	uint32_t height;	//physical height
	uint32_t vWidth;	//virtual width
	uint32_t vHeight;	//virtual height
	uint32_t pitch;		//Pitch //TODO figure out what this is...
	uint32_t bitDepth;	//Bit Depth
	uint32_t x;			//Left screen offset
	uint32_t y;			//Top screen offset
	void* pointer;		//Pointer to GPU mirror
	uint32_t size;		//size of GPU mirror
	uint16_t pallete[0];//For 8 bit color
#define PALETTE_ENTRIES		256
};
}
}
#endif /* IO_DISPLAY_FRAMEBUFFERDESCRIPTION_HPP_ */
