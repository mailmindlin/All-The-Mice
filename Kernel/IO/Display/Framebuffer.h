/*
 * Framebuffer.h
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_DISPLAY_FRAMEBUFFER_H_
#define IO_DISPLAY_FRAMEBUFFER_H_

#include <cstdint>
#include "FrameBufferDescription.hpp"
#include "Mailbox.h"
#include "DisplayUtils.hpp"
#include <string.h> //for memset
#include "../../util/synchronize.h"
#include "../../util/util.hpp"
#include "../memaddr.hpp"

namespace Peripherals {
namespace Display {
struct FrameBufferDescription;
} /* namespace Display */
} /* namespace Peripherals */

namespace Peripherals {
namespace Display {

class FrameBuffer {
public:
	FrameBuffer(uint32_t width, uint32_t height, uint32_t depth);
	virtual ~FrameBuffer();

#if COLOR_DEPTH == 8
	void setPallete(uint8_t index, uint16_t color);
#else
	void setPallete(uint8_t index, uint16_t color) {color=index=color;}
#endif

	bool init();

	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getPitch() const;
	uint32_t getDepth() const;
	void* getBuffer() const;
	uint32_t getSize() const;
protected:
	volatile FrameBufferDescription *fb;
	MailBox mailbox;
};

} /* namespace Display */
} /* namespace Peripherals */

#endif /* IO_DISPLAY_FRAMEBUFFER_H_ */
