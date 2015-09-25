/*
 * GraphicsUtil.cpp
 *
 *  Created on: Sep 25, 2015
 *      Author: wfeehery
 */

#include "GraphicsUtil.h"

namespace Graphics {
namespace Simple {

void rotateAround(float cx, float cy, float angle, Point2D& p) {
	//relative to center
	float rtcx = p.x-cx;
	float rtcy = p.y-cy;

	float s = sin(angle);
	float c = cos(angle);

	p.x = rtcx * c - rtcy * s + cx;
	p.y = rtcx * s + rtcy * c + cx;
}

} /* namespace Simple */
} /* namespace Graphics */
