/*
 * Framebuffer.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "Framebuffer.h"


namespace Peripherals {
namespace Display {

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, uint32_t depth):mailbox(CHANNEL_FRAMEBUFFER) {
	if((width == 0) || (height == 0)) {
		//TODO detect screen size
	}
	if(depth == 8) {
		this->fb = (FrameBufferDescription*)new uint8_t[sizeof(FrameBufferDescription) + PALETTE_ENTRIES * sizeof (uint16_t)];
		memset((void*)fb->pallete, 0, PALETTE_ENTRIES * sizeof(uint16_t));
	} else
		this->fb = new FrameBufferDescription;
	this->fb->width = width;
	this->fb->height = height;
	this->fb->vWidth = width;
	this->fb->vHeight = height;
	this->fb->pitch = 0;
	this->fb->bitDepth = depth;
	this->fb->x = 0;
	this->fb->y = 0;
	this->fb->pointer = 0;
	this->fb->size = 0;

}

FrameBuffer::~FrameBuffer() {
	delete this->fb;
}

bool FrameBuffer::init() {
	CleanDataCache ();
	DataSyncBarrier ();

	uint32_t result = mailbox.writeRead(MemoryMap::GPU_BASE + ((uint32_t)this->fb));

	InvalidateDataCache ();

	return (result!=0) && (fb->pointer != 0);
}
#if COLOR_DEPTH == 8
void FrameBuffer::setPallete(uint8_t index, uint16_t color) {
	if(fb->bitDepth == 8)
		fb->pallete[index] = color;
}
#endif

uint32_t FrameBuffer::getWidth() const {
	return fb->width;
}

uint32_t FrameBuffer::getHeight() const {
	return fb->height;
}

uint32_t FrameBuffer::getPitch() const {
	return fb->pitch;
}

uint32_t FrameBuffer::getDepth() const {
	return fb->bitDepth;
}

void* FrameBuffer::getBuffer() const {
	return fb->pointer;
}

uint32_t FrameBuffer::getSize() const {
	return fb->size;
}

} /* namespace Display */
} /* namespace Peripherals */
