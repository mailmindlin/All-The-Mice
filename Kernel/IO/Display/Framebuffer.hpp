/*
 * Framebuffer.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef IO_DISPLAY_FRAMEBUFFER_HPP_
#define IO_DISPLAY_FRAMEBUFFER_HPP_

#include <stddef.h>
#include <stdlib.h>
#include <cstdint>

#include "../../stdasm.cpp"
#include "postman.hpp"

template<typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

//assembly stuff
extern "C" struct FrameBufferDescription {
	uint32_t width = 1024; //physical width
	uint32_t height = 768;  //physical height
	uint32_t vWidth = 1024; //virtual width
	uint32_t vHeight = 768;  //virtual height
	uint32_t pitch = 0;    //Pitch //TODO figure out what this is...
	uint32_t bitDepth = 16;   //Bit Depth
	uint32_t x = 0;    //Left screen offset
	uint32_t y = 0;    //Top screen offset
	void* pointer = 0;    //Pointer to GPU mirror
	uint32_t size = 0;    //size of GPU mirror
};
extern "C" FrameBufferDescription* InitialiseFrameBuffer(uint32_t w, uint32_t h,
		uint32_t bd);
namespace Displays {
namespace GPU {
FrameBufferDescription* initFrameBuffer(uint32_t w, uint32_t h, uint32_t bd) {
	return InitialiseFrameBuffer(w, h, bd);
}
FrameBufferDescription* cinitFrameBuffer(uint32_t w, uint32_t h, uint32_t vw,
		uint32_t vh, uint32_t bd) {
	FrameBufferDescription* fb = (FrameBufferDescription*) malloc(
			sizeof(FrameBufferDescription));
	fb->width = w;
	fb->height = h;
	fb->vWidth = vw;
	fb->vHeight = vh;
	fb->bitDepth = bd;
	writeMailbox(CHANNEL_FRAMEBUFFER, (uint32_t) fb + 0x40000000); //the +0x40000000 forces the GPU to flush its cache
	uint32_t result = readMailbox(CHANNEL_FRAMEBUFFER);
	if (result == 0) {
		free(fb);
		return 0;
	}
	return fb;
}
FrameBufferDescription* cinitFrameBuffer(uint32_t w, uint32_t h, uint32_t bd) {
	return cinitFrameBuffer(w, h, w, h, bd);
}
inline void setPixel(FrameBufferDescription* fb, uint32_t x, uint32_t y,
		uint16_t c) {
	ASM::write16((uint32_t) fb->pointer + (x + (y * fb->vWidth)) * 2, c);
}
void drawLine(FrameBufferDescription* fb, int x1, int y1, int const x2, int const y2, uint16_t c) {
	int delta_x(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = abs(delta_x) << 1;
	int delta_y(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = abs(delta_y) << 1;
	setPixel(fb, x1, y1, c);
	if (delta_x >= delta_y) {
		// error may go below zero
		int error(delta_y - (delta_x >> 1));
		while (x1 != x2) {
			if ((error >= 0) && (error || (ix > 0))) {
				error -= delta_x;
				y1 += iy;
			}
			// else do nothing
			error += delta_y;
			x1 += ix;
			setPixel(fb, x1, y1, c);
		}
	} else {
		// error may go below zero
		int error(delta_x - (delta_y >> 1));
		while (y1 != y2) {
			if ((error >= 0) && (error || (iy > 0))) {
				error -= delta_y;
				x1 += ix;
			}
			// else do nothing
			error += delta_x;
			y1 += iy;
			setPixel(fb, x1, y1, c);
		}
	}
}
//modified from http://www.coranac.com/tonc/text/text.htm
const uint64_t toncfontTiles[96]=
{
    0x0000000000000000, 0x1818181800180018, 0x0000363600000000, 0x367F36360036367F,
    0x3C067C1800183E60, 0x1B3566000033566C, 0x6E16361C00DE733B, 0x000C181800000000,
    0x0C0C18300030180C, 0x3030180C000C1830, 0xFF3C66000000663C, 0x7E18180000001818,
    0x000000000C181800, 0x7E00000000000000, 0x0000000000181800, 0x183060C00003060C,
    0x7E76663C003C666E, 0x181E1C1800181818, 0x3060663C007E0C18, 0x3860663C003C6660,
    0x33363C380030307F, 0x603E067E003C6660, 0x3E060C38003C6666, 0x3060607E00181818,
    0x3C66663C003C6666, 0x7C66663C001C3060, 0x0018180000181800, 0x001818000C181800,
    0x0618600000006018, 0x007E00000000007E, 0x6018060000000618, 0x3060663C00180018,

    0x5A5A663C003C067A, 0x7E66663C00666666, 0x3E66663E003E6666, 0x06060C7800780C06,
    0x6666361E001E3666, 0x1E06067E007E0606, 0x1E06067E00060606, 0x7606663C007C6666,
    0x7E66666600666666, 0x1818183C003C1818, 0x60606060003C6660, 0x0F1B33630063331B,
    0x06060606007E0606, 0x6B7F776300636363, 0x7B6F676300636373, 0x6666663C003C6666,
    0x3E66663E00060606, 0x3333331E007E3B33, 0x3E66663E00666636, 0x3C0E663C003C6670,
    0x1818187E00181818, 0x66666666003C6666, 0x6666666600183C3C, 0x6B6363630063777F,
    0x183C66C300C3663C, 0x183C66C300181818, 0x0C18307F007F0306, 0x0C0C0C3C003C0C0C,
    0x180C060300C06030, 0x3030303C003C3030, 0x00663C1800000000, 0x00000000003F0000,

    0x0030181800000000, 0x603C0000007C667C, 0x663E0606003E6666, 0x063C0000003C0606,
    0x667C6060007C6666, 0x663C0000003C067E, 0x0C3E0C38000C0C0C, 0x667C00003C607C66,
    0x663E060600666666, 0x1818001800301818, 0x303000301E303030, 0x366606060066361E,
    0x1818181800301818, 0x7F3700000063636B, 0x663E000000666666, 0x663C0000003C6666,
    0x663E000006063E66, 0x667C000060607C66, 0x663E000000060606, 0x063C0000003E603C,
    0x0C3E0C0C00380C0C, 0x66660000007C6666, 0x6666000000183C66, 0x6363000000367F6B,
    0x366300000063361C, 0x666600000C183C66, 0x307E0000007E0C18, 0x0C18183000301818,
    0x1818181800181818, 0x3018180C000C1818, 0x003B6E0000000000, 0x0000000000000000,
};
size_t drawChar(FrameBufferDescription* fb, int x, int y, char chr, uint16_t c) {
	if(chr<0x20 || chr==0x7F)
		return 0;
	//this is why I don't like little-endian ANYTHING. I could have done it much easily if it was BE!!!
	//TODO convert
	uint64_t bitmap = toncfontTiles[chr-0x20];
	uint32_t tmp = bitmap>>32;
	for(int i=0;i<32;i++) {
		if(((tmp>>i) & 0x1)==1)
			setPixel(fb, x+(i%8),y+(i/8),c);
	}
	tmp = bitmap & 0xFFFFFFFF;
	for(int i=0;i<32;i++) {
		if(((tmp>>i) & 0x1)==1)
			setPixel(fb, x+(i%8),y+4+(i/8),c);
	}
	return 8;
}
void drawText(FrameBufferDescription* fb, int x0, int y0, char* text, uint16_t c) {
	int x=x0;
	int y=y0;
	int size;
	while(*text != 0) {
		char chr = *text;
		x+=(size = drawChar(fb,x,y,chr,c));
		if(size==0) {
			if(chr == '\n') {
				x=x0;
				y+=9;
			} else if(chr=='\t') {
				x+=56;
				x+=8-(x%8);
			}
		}
		//go to next char
		text++;
	}
}
const char* hexDigits = "0123456789ABCDEF";
void toHexString(char* str, size_t offset, size_t digits, uint64_t num) {
	char* pos = str+digits+offset;
	for(int i=0;i<digits;i++) {
		*(--pos) = hexDigits[(num>>(i*4)) & 0xF];
	}
}
}
}

#endif /* IO_DISPLAY_FRAMEBUFFER_HPP_ */
