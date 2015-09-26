#include "DisplayUtils.cpp"
namespace Peripherals {
namespace Display {
struct DisplayStatus
{
	TScreenColor   *pContent;
	uint32_t		state;
	unsigned		cursorX;
	unsigned		cursorY;
	bool			cursorOn;
	TScreenColor	color;
	bool			insertOn;
	uint32_t		param1;
	uint32_t		param2;
	bool			updated;
};
}}
