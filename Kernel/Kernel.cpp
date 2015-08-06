/*
 * kernel.c
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#include "Kernel.hpp"

#include <stdlib.h>
#include <cstdint>

#include "IO/Display/DisplayDevice.h"
#include "IO/Display/DisplayUtils.hpp"

#define height 768
#define width 1024
extern "C" void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
	(void) r0;
	(void) r1;
	(void) atags;
	blink(5,0x70000);
	Peripherals::Display::DisplayDevice* screen = new Peripherals::Display::DisplayDevice(width, height, false);
	if (!screen->init()) {
		blink(5, 0x77777);
		return;
	}
	uint32_t color = COLOR_RGB(247, 28, 132, 255);//nice red 0xF0F0
	screen->drawText(0,0, "Hello, World!", color);
	char* tmp = (char*)calloc(40, sizeof(char));
	tmp[2]=':';
	tmp[21]=tmp[3]=' ';
	tmp[22]=tmp[4]='0';
	tmp[23]=tmp[5]='x';
	for(uint8_t i=0;i<92;i++) {
		tmp[0]=i;
		uint64_t bmp = Peripherals::Display::toncfontTiles[i];
		toHexString(tmp,5,16,bmp);
		uint64_t reversified = ((bmp&0xFFFFFFFF00000000)>>32) | ((bmp & 0xFFFFFFFF)<<32);
		toHexString(tmp,24,16,reversified);
		screen->drawText(0,i*8+8, tmp, color);
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
