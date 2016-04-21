#include "InternalPin.hpp"
namespace Peripherals {
	GPIO::InternalPin::InternalPin(uint32_t pin) : pin(pin) {
		if (pin > RPI_BUILTIN_GPIO_SIZE)
			throw std::invalid_argument("Invalid pin number");
	}
	bool GPIO::InternalPin::setFunction(uint8_t fn) {
		if (fn > 0b111)
			return false;
		REG32RW* fselPtr = GPIO_REGS + ((pin / 10) << 2);
		uint8_t offset = (pin % 10) * 3;
		*fselPtr = ((*fselPtr) & (0xFFFFFFFF - (0x7 << offset)))|(fn << offset);
		return true;
	}
	bool GPIO::InternalPin::digitalWrite(bool on) {
		REG32WO* ptr;
		if (pin > 32)
			ptr = on ? &(GPIO_REGS->GPSET1) : &(GPIO_REGS->GPCLR1);
		else
			ptr = on ? &(GPIO_REGS->GPSET0) : &(GPIO_REGS->GPCLR0);
		
		ptr = 1 << (pin % 32);
		
		return true;
	}
	bool GPIO::InternalPin::analogWrite(double value) {
		return digitalWrite(value > 0);
	}
	bool GPIO::InternalPin::pwmWrite(uint32_t data) {
		//TODO finish
		return false;
	}
	bool GPIO::InternalPin::digitalRead() {
		//TODO finish
		return false;
	}
	double GPIO::InternalPin::analogRead() {
		return digitalRead() ? 3.3 : 0;
	}
	bool GPIO::InternalPin::setPUDMode(uint8_t mode) {
		//TODO finish
		return false;
	}
	GPIO::InternalPin::~InternalPin() {
		
	}
}