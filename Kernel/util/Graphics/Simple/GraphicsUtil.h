/*
 * GraphicsUtil.h
 *
 *  Created on: Sep 25, 2015
 *      Author: wfeehery
 */

#ifndef UTIL_GRAPHICS_SIMPLE_GRAPHICSUTIL_H_
#define UTIL_GRAPHICS_SIMPLE_GRAPHICSUTIL_H_

#include "Point2D.h"
#include <cmath>

namespace Graphics {
namespace Simple {


	void rotateAround(float x, float y, float angle, Point2D& p);

} /* namespace Simple */
} /* namespace Graphics */

#endif /* UTIL_GRAPHICS_SIMPLE_GRAPHICSUTIL_H_ */
