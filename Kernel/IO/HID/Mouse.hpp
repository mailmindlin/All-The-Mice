/*
 * Mouse.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_HID_MOUSE_HPP_
#define IO_HID_MOUSE_HPP_

namespace Peripherals {
namespace HID {
class Mouse {
public:
	Mouse();
	int32_t getDeltaX();
	int32_t getDeltaY();
	int32_t getDeltaScroll();
	int8_t getButtons();
};
}
}


#endif /* IO_HID_MOUSE_HPP_ */
