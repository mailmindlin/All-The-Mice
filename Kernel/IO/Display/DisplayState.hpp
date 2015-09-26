/*
 * DisplayState.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#ifndef IO_DISPLAY_DISPLAYSTATE_CPP_
#define IO_DISPLAY_DISPLAYSTATE_CPP_
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
#endif /* IO_DISPLAY_DISPLAYSTATE_CPP_ */
