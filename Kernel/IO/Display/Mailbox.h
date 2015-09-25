/*
 * Mailbox.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#ifndef IO_DISPLAY_MAILBOX_H_
#define IO_DISPLAY_MAILBOX_H_

#include <cstdint>
#include "../../util/stdasm.cpp"
#include "../memaddr.hpp"

namespace Peripherals {
namespace Display {
#define MAILBOX_STATUS_EMPTY 0x40000000
#define MAILBOX_STATUS_FULL	0x80000000
typedef enum {
	CHANNEL_POWER_MANAGEMENT = 0,
	CHANNEL_FRAMEBUFFER = 1,
	CHANNEL_VIRTUAL_UART = 2,
	CHANNEL_VCHIQ = 3,
	CHANNEL_LED = 4,
	CHANNEL_BUTTONS = 5,
	CHANNEL_TOUCH_SCREEN = 6,
	CHANNEL_UNDEFINED = 7,
	CHANNEL_ARM_VC_PROPERTY_TAGS = 8,
	CHANNEL_VC_ARM_PROPERTY_TAGS = 9,
} MAILBOX_CHANNEL_T;
class MailBox {
public:
	MailBox(MAILBOX_CHANNEL_T channel);
	~MailBox(void);

	uint32_t writeRead(uint32_t data);

	void flush(void);

	uint32_t read(void);
	bool write(uint32_t data);

private:
	uint32_t channel;

//	CSpinLock m_SpinLock;
};

} /* namespace Display */
} /* namespace Peripherals */

#endif /* IO_DISPLAY_MAILBOX_H_ */
