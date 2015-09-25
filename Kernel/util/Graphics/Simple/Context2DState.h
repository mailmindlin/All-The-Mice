/*
 * Context2DState.h
 *
 *  Created on: Sep 25, 2015
 *      Author: wfeehery
 */

#ifndef UTIL_GRAPHICS_SIMPLE_CONTEXT2DSTATE_H_
#define UTIL_GRAPHICS_SIMPLE_CONTEXT2DSTATE_H_

namespace Graphics {
namespace Simple {

class Context2DState {
public:
	Context2DState();
	Context2DState(Context2DState& parent);
	virtual ~Context2DState();
	float getLineWidth() const;
	void setLineWidth(float width);
protected:

};

} /* namespace Simple */
} /* namespace Graphics */

#endif /* UTIL_GRAPHICS_SIMPLE_CONTEXT2DSTATE_H_ */
