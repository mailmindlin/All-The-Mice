/*
 * Context2D.cpp
 *
 *  Created on: Sep 25, 2015
 *      Author: wfeehery
 */

#include "Context2D.h"

namespace Graphics {
namespace Simple {

Context2D::Context2D(DisplayDevice* display) {
	// TODO Auto-generated constructor stub

}

Context2D::~Context2D() {
	// TODO Auto-generated destructor stub
}

void Context2D::clearRect(u32 x, u32 y, u32 width, u32 height) {
}

void Context2D::fillRect(u32 x, u32 y, u32 width, u32 height) {
}

void Context2D::strokeRect(u32 x, u32 y, u32 width, u32 height) {
}

void Context2D::setLineWidth(float width) {
}

float Context2D::getLineWidth() const {
}

void Context2D::setFillColor(TScreenColor color) {
}

TScreenColor Context2D::getFillColor() const {
}

void Context2D::setStrokeColor(TScreenColor color) {
}

TScreenColor Context2D::getStrokeColor() const {
}

void Context2D::setAlpha(float alpha) {
}

Gradient2D* Context2D::createLinearGradient(u32 x0, u32 y0, u32 x1, u32 y1) {
}

Gradient2D* Context2D::createRadialGradient(u32 x0, u32 y0, u32 r0, u32 x1,
		u32 y1, u32 r1) {
}

void Context2D::beginPath() {
}

void Context2D::closePath() {
}

void Context2D::moveTo(u32 x, u32 y) {
}
void Context2D::moveTo(Point2D &p) {
	this->moveTo(p.x, p.y);
}

void Context2D::lineTo(u32 x, u32 y) {
}

void Context2D::bezierCurveTo(u32 cp1x, u32 cp1y, u32 cp2x, u32 cp2y, u32 x,
		u32 y) {
}

void Context2D::quadraticCurveTo(u32 cpx, u32 cpy, u32 x, u32 y) {
}

void Context2D::arc(u32 x, u32 y, u32 radius, float startAngle, float endAngle,
		bool counterclockwise) {
}

void Context2D::arcTo(u32 x0, u32 y0, u32 x1, u32 y1, u32 radius) {
}

void Context2D::ellipse(float centerX, float centerY, float radiusX, float radiusY, float rotation,
		float startAngle, float endAngle, bool counterclockwise) {
	Point2D firstPoint;
	Point2D currentPoint;
	float z = 0.99;

	//calculate first point (on the top of the ellipse)
	firstPoint.x = centerX;
	firstPoint.y = centerY + radiusY;
	rotateAround(centerX, centerY, rotation, firstPoint);
	//move to first point (on top)
	this->moveTo(firstPoint);

	for (int i = 1; i < SEGMENTS; i++) {
		float rad = float(i)/float(SEGMENTS) * PI * 2.00;
		currentPoint.x = centerX + radiusX * sin(rad);
		currentPoint.y = centerY + radiusY * cos(rad);

		rotateAround(centerX, centerY, rotation, currentPoint);

		this->lineTo(currentPoint);
	}

	this->lineTo(firstPoint);
}

void Context2D::rect(u32 x, u32 y, u32 width, u32 height) {

}

void Context2D::fill() {
}

void Context2D::stroke() {

}

void Context2D::save() {
	stateStack->push(new Context2DState(stateStack->pop()));
}

void Context2D::restore() {
	if (this->stateStack->size()==1)
		return;
	stateStack->pop();
}

} /* namespace Graphics */
} /* namespace Simple */
