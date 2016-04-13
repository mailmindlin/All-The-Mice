/*
 * DisplayDevice.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#ifndef IO_DISPLAY_DISPLAYDEVICE_H_
#define IO_DISPLAY_DISPLAYDEVICE_H_

#include <cstdint>
#include <stddef.h>
#include <cstdlib>

#include "../Device.h"
#include "DisplayState.hpp"
#include "DisplayStatus.hpp"
#include "DisplayUtils.cpp"
#include "Framebuffer.h"

namespace Peripherals {
namespace Display {
//modified from http://www.coranac.com/tonc/text/text.htm
const uint64_t toncfontTiles[96] = { 0x0000000000000000, 0x1818181800180018, 0x0000363600000000, 0x367F36360036367F,
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

class DisplayDevice: public Device {
public:
	DisplayDevice(uint32_t width, uint32_t height, bool bVirtual = false);
	virtual ~DisplayDevice();

	/**
	 * Initializes the display
	 */
	bool init();

	/**
	 * Get the width of the display
	 */
	uint32_t getWidth() const;
	/**
	 * Get the height of the display
	 */
	uint32_t getHeight() const;

	/**
	 * Set the color of a pixel at the given X and Y coordinates.
	 * Fails silently if (x, y) is not a valid position on the screen.
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param color color to set pixel
	 */
	void setPixel(uint32_t x, uint32_t y, TScreenColor color);
	/**
	 * Gets the color of a pixel at the given X and Y coordinates.
	 * Returns black if (x, y) is not a valid position on the screen.
	 * @param x x coordinate
	 * @param y y coordinate
	 */
	TScreenColor getPixel(uint32_t x, uint32_t y);

	/**
	 * Draws a line of the given color between the given pixels.
	 * No antialiasing.
	 * @param x0 X coordinate of starting point
	 * @param y0 Y coordinate of starting point
	 * @param x1 X coordinate of ending point
	 * @param x1 Y coordinate of ending point
	 * @param color color to draw in
	 */
	void drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, TScreenColor color);
	/**
	 * Draw a character at the given X and Y position.
	 */
	size_t drawChar(uint32_t x, uint32_t y, char c, TScreenColor color);
	/**
	 * Draw a string at the given coordinates.
	 */
	void drawText(uint32_t x, uint32_t y, char* c, size_t length, TScreenColor color);
protected:
	uint32_t initWidth;
	uint32_t initHeight;
	bool isVirtual;
	FrameBuffer *frameBuffer;
	TScreenColor *buffer;
	uint32_t soBuffer;
	uint32_t width;
	uint32_t height;
//	uint32_t state;
//	CSpinLock spinLock;

};

} /* namespace Display */
} /* namespace Peripherals */

#endif /* IO_DISPLAY_DISPLAYDEVICE_H_ */
