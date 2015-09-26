/*
 * Canvas2D.h
 *
 *  Created on: Sep 25, 2015
 *      Author: wfeehery
 */

#ifndef UTIL_GRAPHICS_SIMPLE_CANVAS2D_H_
#define UTIL_GRAPHICS_SIMPLE_CANVAS2D_H_

namespace Graphics {
namespace Simple {

#include <IO/Display/DisplayUtils.h>

class Context2D {
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	TScreenColor getPixel(uint32_t x, uint32_t y) const;
	void setPixel(uint32_t x, uint32_t y, TScreenColor c);

	Context2D getContext2D();
};
}
}

#endif /* UTIL_GRAPHICS_SIMPLE_CANVAS2D_H_ */
