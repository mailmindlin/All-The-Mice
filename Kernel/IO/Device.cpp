/*
 * Device.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "Device.h"
#include <iostream>
namespace Peripherals {

Device::Device(void) {
}

Device::~Device(void) {
	this->unregisterDevice();
}

std::string* Device::getName() {
	std::string* str = new std::string("Unknown Device #");
	*str << getId();
	return str;
}
uint16_t Device::getId() {
	return this->id;
}
void Device::registerDevice() {
	DeviceManager* manager = DeviceManager::getInstance();
	return manager->registerDevice(this);
}
bool Device::unregisterDevice() {
	DeviceManager* manager = DeviceManager::getInstance();
	if (manager->unregisterDevice(getId())) {
		this->setId(-1);
		return true;
	} else {
		return false;
	}
}
bool Device::setId(uint16_t id) {
	this->id = id;
	return true;
}


} /* namespace Peripherals */

