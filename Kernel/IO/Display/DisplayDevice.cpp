/*
 * DisplayDevice.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "DisplayDevice.h"

namespace Peripherals {
namespace Display {
//modified from http://www.coranac.com/tonc/text/text.htm
static const uint64_t toncfontTiles[96] = { 0x0000000000000000, 0x1818181800180018, 0x0000363600000000, 0x367F36360036367F,
		0x3C067C1800183E60, 0x1B3566000033566C, 0x6E16361C00DE733B, 0x000C181800000000, 0x0C0C18300030180C,
		0x3030180C000C1830, 0xFF3C66000000663C, 0x7E18180000001818, 0x000000000C181800, 0x7E00000000000000,
		0x0000000000181800, 0x183060C00003060C, 0x7E76663C003C666E, 0x181E1C1800181818, 0x3060663C007E0C18,
		0x3860663C003C6660, 0x33363C380030307F, 0x603E067E003C6660, 0x3E060C38003C6666, 0x3060607E00181818,
		0x3C66663C003C6666, 0x7C66663C001C3060, 0x0018180000181800, 0x001818000C181800, 0x0618600000006018,
		0x007E00000000007E, 0x6018060000000618, 0x3060663C00180018,

		0x5A5A663C003C067A, 0x7E66663C00666666, 0x3E66663E003E6666, 0x06060C7800780C06, 0x6666361E001E3666,
		0x1E06067E007E0606, 0x1E06067E00060606, 0x7606663C007C6666, 0x7E66666600666666, 0x1818183C003C1818,
		0x60606060003C6660, 0x0F1B33630063331B, 0x06060606007E0606, 0x6B7F776300636363, 0x7B6F676300636373,
		0x6666663C003C6666, 0x3E66663E00060606, 0x3333331E007E3B33, 0x3E66663E00666636, 0x3C0E663C003C6670,
		0x1818187E00181818, 0x66666666003C6666, 0x6666666600183C3C, 0x6B6363630063777F, 0x183C66C300C3663C,
		0x183C66C300181818, 0x0C18307F007F0306, 0x0C0C0C3C003C0C0C, 0x180C060300C06030, 0x3030303C003C3030,
		0x00663C1800000000, 0x00000000003F0000,

		0x0030181800000000, 0x603C0000007C667C, 0x663E0606003E6666, 0x063C0000003C0606, 0x667C6060007C6666,
		0x663C0000003C067E, 0x0C3E0C38000C0C0C, 0x667C00003C607C66, 0x663E060600666666, 0x1818001800301818,
		0x303000301E303030, 0x366606060066361E, 0x1818181800301818, 0x7F3700000063636B, 0x663E000000666666,
		0x663C0000003C6666, 0x663E000006063E66, 0x667C000060607C66, 0x663E000000060606, 0x063C0000003E603C,
		0x0C3E0C0C00380C0C, 0x66660000007C6666, 0x6666000000183C66, 0x6363000000367F6B, 0x366300000063361C,
		0x666600000C183C66, 0x307E0000007E0C18, 0x0C18183000301818, 0x1818181800181818, 0x3018180C000C1818,
		0x003B6E0000000000, 0x0000000000000000, };

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
	if (c < 0x20 || c == 0x7F)//C0 control character or DEL
		return 0;
	if (c == 0x20)//space
		return 8;
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

void DisplayDevice::drawText(uint32_t x0, uint32_t y0, char* str, size_t length, TScreenColor color) {
	uint32_t x = x0;
	uint32_t y = y0;
	char chr;
	while (length-- > 0) {
		char chr = *str++;
		size_t width;
		x+= (width = drawChar(x, y, chr, color));
		if (width == 0) {
			switch (chr) {
				case '\r':
					x = x0;
				case '\n':
					y+= 9;
					break;
				case '\t':
					x += 56;
					x += 8 - (x % 8);//align
					break;
			}
		}
		if (x > getWidth())
			x = x0;
	}
}

} /* namespace Display */
} /* namespace Peripherals */
