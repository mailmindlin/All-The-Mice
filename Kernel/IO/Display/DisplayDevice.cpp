/*
 * DisplayDevice.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "DisplayDevice.h"

namespace Peripherals {
namespace Display {

DisplayDevice::DisplayDevice(uint32_t width, uint32_t height, bool isVirtual) :
		initWidth(width), initHeight(height), isVirtual(isVirtual), frameBuffer(0), buffer(0),
		soBuffer(0), width(0), height(0){
}

DisplayDevice::~DisplayDevice() {
	if (isVirtual) {
		delete[] buffer;
	}
	buffer = 0;

	delete frameBuffer;
	frameBuffer = 0;
}

bool DisplayDevice::init() {
	if(!isVirtual) {
		frameBuffer = new FrameBuffer(initWidth, initHeight, COLOR_DEPTH);
		#if COLOR_DEPTH == 8
			frameBuffer->setPallete(COLOR_NORMAL, COLOR_NORMAL16);
			frameBuffer->setPallete(COLOR_HIGH, COLOR_HIGH16);
			frameBuffer->setPallete(COLOR_HALF, COLOR_HALF16);
		#endif
		if((!frameBuffer->init()) || (frameBuffer->getDepth() != COLOR_DEPTH))
			return false;
		width = frameBuffer->getWidth();
		height = frameBuffer->getHeight();
		buffer = (TScreenColor*)frameBuffer->getBuffer();
		soBuffer = frameBuffer->getSize();

		// Makes things easier and is normally the case
		if (frameBuffer->getPitch () != width * sizeof (TScreenColor))
			return false;
	} else {
		width = initWidth;
		height = initHeight;
		soBuffer = width * height * sizeof (TScreenColor);
		buffer = new TScreenColor[width * height];
	}
	return true;
}

uint32_t DisplayDevice::getWidth() const {
	return width;
}

uint32_t DisplayDevice::getHeight() const {
	return height;
}

void DisplayDevice::setPixel(uint32_t x, uint32_t y, TScreenColor color) {
	if(x<width && y<height)
		buffer[x + (y*getWidth())] = color;
}

TScreenColor DisplayDevice::getPixel(uint32_t x, uint32_t y) {
	if(x<width && y<height)
		return buffer[x + (y*getWidth())];
	return COLOR_BLACK;
}

void DisplayDevice::drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, TScreenColor color) {
	int delta_x(x1 - x0);
	// if x0 == x1, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = abs(delta_x) << 1;
	int delta_y(y1 - y0);
	// if y0 == y1, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = abs(delta_y) << 1;
	setPixel(x0, y0, color);
	if (delta_x >= delta_y) {
		// error may go below zero
		int error(delta_y - (delta_x >> 1));
		while (x0 != x1) {
			if ((error >= 0) && (error || (ix > 0))) {
				error -= delta_x;
				y0 += iy;
			}
			// else do nothing
			error += delta_y;
			x0 += ix;
			setPixel(x0, y0, color);
		}
	} else {
		// error may go below zero
		int error(delta_x - (delta_y >> 1));
		while (y0 != y1) {
			if ((error >= 0) && (error || (iy > 0))) {
				error -= delta_y;
				x0 += ix;
			}
			// else do nothing
			error += delta_x;
			y0 += iy;
			setPixel(x0, y0, color);
		}
	}
}
size_t DisplayDevice::drawChar(uint32_t x, uint32_t y, char c, TScreenColor color) {
	if (c < 0x20 || c == 0x7F)
		return 0;
	//this is why I don't like little-endian ANYTHING. I could have done it much easily if it was BE!!!
	//TODO convert
	uint64_t bitmap = toncfontTiles[c - 0x20];
	uint32_t tmp = bitmap >> 32;
	for (int i = 0; i < 32; i++) {
		if (((tmp >> i) & 0x1) == 1)
			setPixel(x + (i % 8), y + (i / 8), color);
	}
	tmp = bitmap & 0xFFFFFFFF;
	for (int i = 0; i < 32; i++) {
		if (((tmp >> i) & 0x1) == 1)
			setPixel(x + (i % 8), y + 4 + (i / 8), color);
	}
	return 8;
}

void DisplayDevice::drawText(uint32_t x0, uint32_t y0, char* text, TScreenColor color) {
	uint32_t x = x0;
	uint32_t y = y0;
	size_t size;
	while (*text != 0) {
		char chr = *text;
		x += (size = drawChar(x, y, chr, color));
		if (size == 0) {
			if (chr == '\n') {
				x = x0;
				y += 9;
			} else if (chr == '\t') {
				x += 56;
				x += 8 - (x % 8);
			}
		}
		//go to next char
		text++;
	}
}

} /* namespace Display */
} /* namespace Peripherals */
