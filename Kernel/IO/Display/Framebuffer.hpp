/*
 * Framebuffer.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_DISPLAY_FRAMEBUFFER_HPP_
#define IO_DISPLAY_FRAMEBUFFER_HPP_

#include <stdlib.h>
#include <cstdint>

#include "../../stdasm.cpp"
#include "postman.hpp"

template<typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

//assembly stuff
extern "C" struct FrameBufferDescription {
	uint32_t width = 1024; //physical width
	uint32_t height = 768;  //physical height
	uint32_t vWidth = 1024; //virtual width
	uint32_t vHeight = 768;  //virtual height
	uint32_t pitch = 0;    //Pitch //TODO figure out what this is...
	uint32_t bitDepth = 16;   //Bit Depth
	uint32_t x = 0;    //Left screen offset
	uint32_t y = 0;    //Top screen offset
	void* pointer = 0;    //Pointer to GPU mirror
	uint32_t size = 0;    //size of GPU mirror
};
extern "C" FrameBufferDescription* InitialiseFrameBuffer(uint32_t w, uint32_t h,
		uint32_t bd);
namespace Displays {
namespace GPU {
FrameBufferDescription* initFrameBuffer(uint32_t w, uint32_t h, uint32_t bd) {
	return InitialiseFrameBuffer(w, h, bd);
}
FrameBufferDescription* cinitFrameBuffer(uint32_t w, uint32_t h, uint32_t vw,
		uint32_t vh, uint32_t bd) {
	FrameBufferDescription* fb = (FrameBufferDescription*) malloc(
			sizeof(FrameBufferDescription));
	fb->width = w;
	fb->height = h;
	fb->vWidth = vw;
	fb->vHeight = vh;
	fb->bitDepth = bd;
	writeMailbox(CHANNEL_FRAMEBUFFER, (uint32_t) fb + 0x40000000); //the +0x40000000 forces the GPU to flush its cache
	uint32_t result = readMailbox(CHANNEL_FRAMEBUFFER);
	if (result == 0) {
		free(fb);
		return 0;
	}
	return fb;
}
FrameBufferDescription* cinitFrameBuffer(uint32_t w, uint32_t h, uint32_t bd) {
	return cinitFrameBuffer(w, h, w, h, bd);
}
inline void setPixel(FrameBufferDescription* fb, uint32_t x, uint32_t y,
		uint16_t c) {
	ASM::write16((uint32_t) fb->pointer + (x + (y * fb->vWidth)) * 2, c);
}
void drawLine(FrameBufferDescription* fb, int x1, int y1, int const x2, int const y2, uint16_t c) {
	int delta_x(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = abs(delta_x) << 1;

	int delta_y(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = abs(delta_y) << 1;

	setPixel(fb, x1, y1, c);

	if (delta_x >= delta_y) {
		// error may go below zero
		int error(delta_y - (delta_x >> 1));

		while (x1 != x2) {
			if ((error >= 0) && (error || (ix > 0))) {
				error -= delta_x;
				y1 += iy;
			}
			// else do nothing

			error += delta_y;
			x1 += ix;

			setPixel(fb, x1, y1, c);
		}
	} else {
		// error may go below zero
		int error(delta_x - (delta_y >> 1));

		while (y1 != y2) {
			if ((error >= 0) && (error || (iy > 0))) {
				error -= delta_y;
				x1 += ix;
			}
			// else do nothing

			error += delta_x;
			y1 += iy;

			setPixel(fb, x1, y1, c);
		}
	}
}
}
}

#endif /* IO_DISPLAY_FRAMEBUFFER_HPP_ */
