/*
 * Device.h
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_DEVICE_H_
#define IO_DEVICE_H_

#include <cstdint>

namespace Peripherals {

class Device {
public:
	Device (void);
	virtual ~Device (void);

	// returns number of read bytes or < 0 on failure
	virtual int32_t read (void *pBuffer, uint32_t nCount);

	// returns number of written bytes or < 0 on failure
	virtual int32_t write (const void *pBuffer, uint32_t nCount);

	// returns the resulting offset, (unsigned long long) -1 on error
	virtual uint64_t seek (uint64_t ullOffset);		// byte offset
};

} /* namespace Peripherals */

#endif /* IO_DEVICE_H_ */
