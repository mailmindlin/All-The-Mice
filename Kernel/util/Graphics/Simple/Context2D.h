/*
 * Context2D.h
 *
 *  Created on: Sep 25, 2015
 *      Author: mailmindlin
 */

#ifndef IO_DISPLAY_CONTEXT2D_CONTEXT2D_H_
#define IO_DISPLAY_CONTEXT2D_CONTEXT2D_H_

#include <cstdint>
#include <cmath>
#include <stack>
#include <IO/Display/DisplayDevice.h>

#include "Context2DState.h"
#include "Gradient2D.h"
#include "Point2D.h"
#include "GraphicsUtil.h"

namespace Graphics {
namespace Simple {

using Peripherals::Display::DisplayDevice;

#define SEGMENTS 12

class Context2D {
public:
	Context2D(DisplayDevice* parent);
	virtual ~Context2D();

	void clearRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	void fillRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	void strokeRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	void setLineWidth(float width);
	float getLineWidth() const;
	void setFillColor(TScreenColor color);
	TScreenColor getFillColor() const;
	void setStrokeColor(TScreenColor color);
	TScreenColor getStrokeColor() const;
	void setAlpha(float alpha);
	float getAlpha() const;
	

	Gradient2D* createLinearGradient(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
	Gradient2D* createRadialGradient(uint32_t x0, uint32_t y0, uint32_t r0, uint32_t x1, uint32_t y1, uint32_t r1);

	void beginPath();
	void closePath();
	void moveTo(Point2D& p);
	void moveTo(uint32_t x, uint32_t y);
	void moveTo(float x, float y);
	void lineTo(Point2D& p);
	void lineTo(uint32_t x, uint32_t y);
	void lineTo(float x, float y);
	void bezierCurveTo(uint32_t cp1x, uint32_t cp1y, uint32_t cp2x, uint32_t cp2y, uint32_t x, uint32_t y);
	void quadraticCurveTo(uint32_t cpx, uint32_t cpy, uint32_t x, uint32_t y);
	void arc(uint32_t x, uint32_t y, uint32_t radius, float startAngle, float endAngle) {
		this->arc(x,y,radius,startAngle, endAngle, false);
	};
	void arc(uint32_t x, uint32_t y, uint32_t radius, float startAngle, float endAngle, bool counterclockwise);
	void arcTo(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t radius);
	void ellipse(float x, float y, float radiusX, float radiusY, float rotation, float startAngle, float endAngle) {
		this->ellipse(x,y,radiusX, radiusY, rotation, startAngle, endAngle);
	};
	void ellipse(uint32_t x, uint32_t y, uint32_t radiusX, uint32_t radiusY, float rotation, float startAngle, float endAngle) {
		this->ellipse(x,y,radiusX, radiusY, rotation, startAngle, endAngle);
	};
	void ellipse(uint32_t x, uint32_t y, uint32_t radiusX, uint32_t radiusY, float rotation, float startAngle, float endAngle, bool counterclockwise);
	void ellipse(float x, float y, float radiusX, float radiusY, float rotation, float startAngle, float endAngle, bool counterclockwise);
	void rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	void fill();
	void stroke();
	
	void save();
	void restore();
protected:
	std::stack <Context2DState*>* stateStack;

};

} /* namespace Graphics */
} /* namespace Simple */

#endif /* IO_DISPLAY_CONTEXT2D_CONTEXT2D_H_ */
