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
	 * Draws a line of the given color between the two given points.
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
