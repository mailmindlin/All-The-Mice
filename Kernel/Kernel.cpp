/*
 * kernel.c
 *
 *  Created on: Aug 5, 2015
 *      Author: mailmindlin
 */

#include "Kernel.hpp"
#include "prelib.h"

#define height 768
#define width 1024
extern "C" void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
	(void) r0;
	(void) r1;
	(void) atags;
	//Blink the light a few times to show that we turned on.
	blink(5,0x70000);
	//Get the screen
	Peripherals::Display::DisplayDevice* screen = new Peripherals::Display::DisplayDevice(width, height, false);
	if (!screen->init()) {
		blink(5, 0x77777);
		return;
	}
	//Draw Hello, World
	TScreenColor redColor = COLOR_RGB(247, 28, 132, 255);//nice red 0xF0F0
	screen->drawText(0, 0, "Hello, World!", 14, redColor);
	
	//Draw header
	TScreenColor greenColor = COLOR_RGB(0, 255, 0, 255); //0x0F0
	screen->drawText(0, 8, "C: LITTLE_ENDIAN_HEX  | 0xBIG_ENDIAN_HEX", 40, greenColor);
	//Filler string
	char* line = "#: 0x7766554433221100 | 0x3322110077665544";
	uint32_t y = 16;
	for(uint8_t i=0;i<127;i++) {
		line[0]=i;
		//Lookup the bitmap for the character.
		uint64_t bmp;
		if (i < 0x20 || i == 127)
			bmp = 0x0000000000000000;
		else
			bmp = Peripherals::Display::toncfontTiles[i - 0x20];
		
		//Fill in the LE hex chars
		toHexString(line,5,16,bmp);
		//Flip the bytes to make it big-endian
		uint64_t reversified = ((bmp>>32) & 0xFFFFFFFF) | ((bmp & 0xFFFFFFFF)<<32);
		//Fill in the BE hex chars
		toHexString(line, 26, 16, reversified);
		
		screen->drawText(0, y, line, 40, color);
		//Go down a line
		y+= 8;
	}
	//Try to draw a box, and use different colors
	//TODO move right, so it doesn't collide with the text drawn above
	screen->drawLine(50, 50, 100, 50, COLOR_RGB(255, 0, 0, 255));//Top, red
	screen->drawLine(50, 100, 100, 100, COLOR_RGB(0, 255, 0, 255));//Bottom, green
	screen->drawLine(50, 50, 50, 100, COLOR_RGB(0, 0, 255, 255));//Left, blue
	screen->drawLine(100, 50, 100, 100, COLOR_RGB(255, 255, 0, 255));//Right, yellow
	screen->drawLine(50, 50, 100, 100, COLOR_RGB(255, 0, 255, 255));//TopLeft/BottomRight diagonal, magenta
	screen->drawLine(50, 100, 100, 50, COLOR_RGB(0, 255, 255, 255));//BottomLeft/TopRight diagonal, cyan
	screen->drawLine(50, 75, 100, 75, COLOR_RGB(255, 255, 255, 255));//MiddleLeft/MiddleRight, white
	while (true) {
		//Stay alive
	}
}
void kernel_shutdown() {

}
void waitABit(uint32_t i) {
	while(i-->0);
}
void blink(uint32_t amt,uint32_t speed) {
	//the base memory address for the GPIO
	unsigned int gpio_base= BCM_BASE + 0x200000;
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
