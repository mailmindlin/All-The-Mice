/*
 * Device.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#ifndef IO_DEVICE_H_
#define IO_DEVICE_H_

#include <cstdint>
#include <string>
#include "DeviceManager.hpp"

namespace Peripherals {

class Device {
	friend class DeviceManager;
	public:
		Device (void);
		virtual ~Device (void);
		virtual std::string* getName();
		uint16_t getId();
	protected:
		virtual bool registerDevice();
		virtual bool unregisterDevice();
	private:
		bool setId(uint16_t id);
		uint16_t id;
};

} /* namespace Peripherals */

#endif /* IO_DEVICE_H_ */
