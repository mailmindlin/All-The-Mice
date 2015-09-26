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

void Context2D::clearRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

}

void Context2D::fillRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
}

void Context2D::strokeRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
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

Gradient2D* Context2D::createLinearGradient(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
}

Gradient2D* Context2D::createRadialGradient(uint32_t x0, uint32_t y0, uint32_t r0, uint32_t x1,
		uint32_t y1, uint32_t r1) {
}

void Context2D::beginPath() {
}

void Context2D::closePath() {
}

void Context2D::moveTo(uint32_t x, uint32_t y) {
}
void Context2D::moveTo(Point2D &p) {
	this->moveTo(p.x, p.y);
}

void Context2D::lineTo(uint32_t x, uint32_t y) {
}

void Context2D::bezierCurveTo(uint32_t cp1x, uint32_t cp1y, uint32_t cp2x, uint32_t cp2y, uint32_t x,
		uint32_t y) {
}

void Context2D::quadraticCurveTo(uint32_t cpx, uint32_t cpy, uint32_t x, uint32_t y) {
}

void Context2D::arc(uint32_t x, uint32_t y, uint32_t radius, float startAngle, float endAngle,
		bool counterclockwise) {
}

void Context2D::arcTo(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t radius) {
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
		float rad = float(i)/float(SEGMENTS) * M_PI * 2.00;
		currentPoint.x = centerX + radiusX * sin(rad);
		currentPoint.y = centerY + radiusY * cos(rad);

		rotateAround(centerX, centerY, rotation, currentPoint);

		this->lineTo(currentPoint);
	}

	this->lineTo(firstPoint);
}

void Context2D::rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

}

void Context2D::fill() {
}

void Context2D::stroke() {

}

void Context2D::save() {
	stateStack->push(new Context2DState(*stateStack->top()));
}

void Context2D::restore() {
	if (this->stateStack->size()==1)
		return;
	stateStack->pop();
}

} /* namespace Graphics */
} /* namespace Simple */
