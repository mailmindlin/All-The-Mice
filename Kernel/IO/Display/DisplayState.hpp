/*
 * DisplayState.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_DISPLAY_DISPLAYSTATE_HPP_
#define IO_DISPLAY_DISPLAYSTATE_HPP_
namespace Peripherals {
namespace Display {
enum TDisplayState
{
	DisplayStateStart,
	DisplayStateEscape,
	DisplayStateBracket,
	DisplayStateNumber1,
	DisplayStateQuestionMark,
	DisplayStateSemicolon,
	DisplayStateNumber2,
	DisplayStateNumber3
};
}
}
#endif /* IO_DISPLAY_DISPLAYSTATE_HPP_ */
