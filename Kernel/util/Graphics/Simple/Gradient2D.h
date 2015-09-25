/*
 * Gradient2D.h
 *
 *  Created on: Sep 25, 2015
 *      Author: wfeehery
 */

#ifndef IO_DISPLAY_CONTEXT2D_GRADIENT2D_H_
#define IO_DISPLAY_CONTEXT2D_GRADIENT2D_H_

namespace Peripherals {
namespace Display {

class Gradient2D {
public:
	Gradient2D();
	virtual ~Gradient2D();
	void addColorStop(double offset, TScreenColor color);
};

} /* namespace Display */
} /* namespace Peripherals */

#endif /* IO_DISPLAY_CONTEXT2D_GRADIENT2D_H_ */
