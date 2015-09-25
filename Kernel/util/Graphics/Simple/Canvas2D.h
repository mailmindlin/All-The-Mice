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
class Context2D {
	u32 getWidth() const;
	u32 getHeight() const;
	TScreenColor getPixel(u32 x, u32 y) const;
	void setPixel(u32 x, u32 y, TScreenColor c);

	Context2D getContext2D();
};
}
}

#endif /* UTIL_GRAPHICS_SIMPLE_CANVAS2D_H_ */
