/*
 * Context2D.h
 *
 *  Created on: Sep 25, 2015
 *      Author: mailmindlin
 */

#ifndef IO_DISPLAY_CONTEXT2D_CONTEXT2D_H_
#define IO_DISPLAY_CONTEXT2D_CONTEXT2D_H_

#include "../DisplayDevice.h"
#include "../DisplayUtils.hpp"
#include "Context2DState.h"
#include "Gradient2D.h"
#include "Point2D.h"
#include "GraphicsUtil.h"
#include <cstdint>
#include <cmath>
#include <stack>

namespace Graphics {
namespace Simple {

using Peripherals::Display::DisplayDevice;

#define SEGMENTS 12

#ifndef __REALCOMP__
typedef unsigned int u32;
//HORRIBLE device to make errors stop annoying you
#define sin(x) x
#define cos(x) x
#define PI 3.1415267
#endif

class Context2D {
public:
	Context2D(DisplayDevice* parent);
	virtual ~Context2D();

	void clearRect(u32 x, u32 y, u32 width, u32 height);
	void fillRect(u32 x, u32 y, u32 width, u32 height);
	void strokeRect(u32 x, u32 y, u32 width, u32 height);

	void setLineWidth(float width);
	float getLineWidth() const;
	void setFillColor(TScreenColor color);
	TScreenColor getFillColor() const;
	void setStrokeColor(TScreenColor color);
	TScreenColor getStrokeColor() const;
	void setAlpha(float alpha);
	float getAlpha() const;
	

	Gradient2D* createLinearGradient(u32 x0, u32 y0, u32 x1, u32 y1);
	Gradient2D* createRadialGradient(u32 x0, u32 y0, u32 r0, u32 x1, u32 y1, u32 r1);

	void beginPath();
	void closePath();
	void moveTo(Point2D& p);
	void moveTo(u32 x, u32 y);
	void moveTo(float x, float y);
	void lineTo(Point2D& p);
	void lineTo(u32 x, u32 y);
	void lineTo(float x, float y);
	void bezierCurveTo(u32 cp1x, u32 cp1y, u32 cp2x, u32 cp2y, u32 x, u32 y);
	void quadraticCurveTo(u32 cpx, u32 cpy, u32 x, u32 y);
	void arc(u32 x, u32 y, u32 radius, float startAngle, float endAngle) {
		this->arc(x,y,radius,startAngle, endAngle, false);
	};
	void arc(u32 x, u32 y, u32 radius, float startAngle, float endAngle, bool counterclockwise);
	void arcTo(u32 x0, u32 y0, u32 x1, u32 y1, u32 radius);
	void ellipse(float x, float y, float radiusX, float radiusY, float rotation, float startAngle, float endAngle) {
		this->ellipse(x,y,radiusX, radiusY, rotation, startAngle, endAngle);
	};
	void ellipse(u32 x, u32 y, u32 radiusX, u32 radiusY, float rotation, float startAngle, float endAngle) {
		this->ellipse(x,y,radiusX, radiusY, rotation, startAngle, endAngle);
	};
	void ellipse(u32 x, u32 y, u32 radiusX, u32 radiusY, float rotation, float startAngle, float endAngle, bool counterclockwise);
	void ellipse(float x, float y, float radiusX, float radiusY, float rotation, float startAngle, float endAngle, bool counterclockwise);
	void rect(u32 x, u32 y, u32 width, u32 height);

	void fill();
	void stroke();
	
	void save();
	void restore();
protected:
	std::stack <Context2DState>* stateStack;

};

} /* namespace Graphics */
} /* namespace Simple */

#endif /* IO_DISPLAY_CONTEXT2D_CONTEXT2D_H_ */
