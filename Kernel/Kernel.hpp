/*
 * Kernel.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: wfeehery17
 */

#ifndef KERNEL_HPP_
#define KERNEL_HPP_
#include <stddef.h>
#include <stdint.h>
#include <cstdint>
#include "IO/Display/Framebuffer.hpp"
extern "C" {
/**
 * Entry point to c++ code
 * @param r0 register 0
 * @param r1 register 1
 * @param atags (not really sure about this one)
 */
extern void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags);
/**
 * Called to shutdown the kernel. Basically, just shutdown all of the peripherals, and release all the
 * memory possible.
 * TODO: add some way for things to add shutdown hooks, to avoid hardcoding every shutdown action into
 * here.
 */
extern void kernel_shutdown();
void blink(uint32_t amt,uint32_t speed);
}


#endif /* KERNEL_HPP_ */
