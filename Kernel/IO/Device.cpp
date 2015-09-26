/*
 * Device.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "Device.h"

namespace Peripherals {

Device::Device(void) {
}

Device::~Device(void) {
}

int32_t Device::read(void* pBuffer, uint32_t nCount) {
	return -1;
}

int32_t Device::write(const void* pBuffer, uint32_t nCount) {
	return -1;
}

uint64_t Device::seek(uint64_t ullOffset) {
	return -1;
}


} /* namespace Peripherals */

