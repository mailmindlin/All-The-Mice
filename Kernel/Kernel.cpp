/*
 * kernel.c
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#include "Kernel.hpp"

#include <cstdint>

#include "IO/Display/Framebuffer.hpp"
#include "stdasm.cpp"

#define height 768
#define width 1024
extern "C" void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
	(void) r0;
	(void) r1;
	(void) atags;
	blink(5,0x70000);
	FrameBufferDescription* result = Displays::GPU::initFrameBuffer(width, height, 16);
	if (result == 0) {
		blink(5, 0x77777);
		return;
	}
	uint32_t color = 0xF0F0;//nice red
	Displays::GPU::drawText(result, 0,0, "Hello, World!", color);
	char* tmp = (char*)calloc(8, sizeof(char));
	for(int i=0;i<50;i++) {
		Displays::GPU::drawText(result, 0,i*8+8, "0x", color);
		Displays::GPU::toHexString(tmp,0,8,ASM::read32(i*4));
		Displays::GPU::drawText(result, 16,i*8+8, tmp, color);
	}
	while (true) {
	}
}
void kernel_shutdown() {

}
void waitABit(uint32_t i) {
	while(i-->0);
}
void blink(uint32_t amt,uint32_t speed) {
	//the base memory address for the GPIO
	unsigned int gpio_base=0x20200000;
	//a value pointing to pin16
	unsigned int pin16 = 1<<16;
	//pointer to GPIO function select
	unsigned int* fsel=(unsigned int*) (gpio_base+4);//FSEL 1
	//pointer to GPIO pin off
	volatile unsigned int* pinOff  = (unsigned int*) (gpio_base+40);
	volatile unsigned int* pinOn = (unsigned int*) (gpio_base+28);
	*fsel=1<<18;
	while(amt--) {
		*pinOff=pin16;
		waitABit(speed);
		*pinOn=pin16;
		waitABit(speed);
	}
}
