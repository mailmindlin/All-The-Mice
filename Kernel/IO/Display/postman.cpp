/*
 * postman.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 * TODO: DEPRECATED
 */

#ifndef IO_DISPLAY_POSTMAN_CPP_
#define IO_DISPLAY_POSTMAN_CPP_

#include <cstdint>

#include "../memaddr.hpp"

using namespace MemoryMap;
namespace Displays {
namespace GPU {
bool writeMailbox(uint8_t channel, uint32_t value);
uint32_t readMailbox(uint8_t channel);
uint32_t readMailbox();
bool canWrite();
bool canRead();
#define MAIL_BASE 0xB880    // Base address for the mailbox registers
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
} MAILBOX_CHANNEL_TYPE;
bool writeMailbox(MAILBOX_CHANNEL_TYPE channel, uint32_t value) {
	if (channel > 15 || (value & 0xF) == 0)
		return false;
	while (!canWrite())
		;
//	*GPU_WRITE = channel | value;
	return true;
}
uint32_t readMailbox(MAILBOX_CHANNEL_TYPE channel) {
	if (channel > 15)
		return false;
	uint32_t mail;
	do {
		mail = readMailbox();
	} while ((mail & 0xF) != channel);
	return mail & 0xfffffff0;
}
bool canWrite() {
	return ((*GPU_STATUS) & 0x80000000) != 0;
}
bool canRead() {
	return ((*GPU_STATUS) & 0x40000000) != 0;
}
uint32_t readMailbox() {
	while (!canRead())
		;
	return *GPU_READ;
}
}
}

#endif /* IO_DISPLAY_POSTMAN_CPP_ */
