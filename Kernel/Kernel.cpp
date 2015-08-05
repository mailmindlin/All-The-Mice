/*
 * kernel.c
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#include "Kernel.hpp"

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
	uint32_t color = 0xF0F0;
	Displays::GPU::drawLine(result, 50,0,500,100,color);
	for(int i=0;i<100;i++)
		Displays::GPU::drawLine(result, rand() % width, rand() % height, rand() % width, rand() % height,color);
	while (true) {
//		uint32_t ptr = (uint32_t) result->pointer;
//		color+=0b100001000001;
//		for (int y = 0; y < height; y++)
//			for (int x = 0; x < width; x++) {
//				Displays::GPU::setPixel(result, x, y, color);
//				if(y>1)
//					Displays::GPU::setPixel(result, x, y-2, 0);
//				ptr += 2;
//			}
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
