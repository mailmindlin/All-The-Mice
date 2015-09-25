/*
 * Mailbox.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "Mailbox.h"

namespace Peripherals {
namespace Display {
MailBox::MailBox(MAILBOX_CHANNEL_T channel) :
		channel(channel) {
}

MailBox::~MailBox(void) {
}

uint32_t MailBox::writeRead(uint32_t data) {
	//TODO add synchronization
	flush();
	if (!write(data))
		return 0;
	uint32_t result = read();
	return result;
}

void MailBox::flush(void) {
	while (!(ASM::readV(MemoryMap::GPU_STATUS) & MAILBOX_STATUS_EMPTY)) {
		ASM::readV(MemoryMap::GPU_READ);
		ASM::delay(20);
		//TODO fix timer to 20ms
	}
}

uint32_t MailBox::read(void) {
	uint32_t result;
	do {
		while (ASM::readV(MemoryMap::GPU_STATUS) & MAILBOX_STATUS_EMPTY)
			;

		result = ASM::readV(MemoryMap::GPU_READ);
	} while ((result & 0xF) != channel);
	return result & ~0xF;
}

bool MailBox::write(uint32_t data) {
	while (ASM::readV(MemoryMap::GPU_STATUS) & MAILBOX_STATUS_FULL)
		;

	if ((data & 0xF) != 0)
		return false;
	ASM::writeV((uint32_t* volatile ) MemoryMap::GPU_WRITE, (uint32_t) (channel | data));// channel number is in the lower 4 bits
	return true;
}

} /* namespace Display */
} /* namespace Peripherals */

