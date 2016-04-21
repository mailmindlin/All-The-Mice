#ifndef IO_GPIO_InternalPin_HPP_
#define IO_GPIO_InternalPin_HPP_
#include <stdexcept>
#include "GPIO.hpp"
namespace Peripherals {
	class GPIO::InternalPin : public GPIO::Pin {
		public:
			InternalPin(uint32_t pin);
			~InternalPin();
			bool setFunction(uint8_t fn);
			bool digitalWrite(bool on);
			bool analogWrite(double value);
			bool pwmWrite(uint32_t data);
			bool digitalRead();
			double analogRead();
			bool setPUDMode(uint8_t mode);
			bool isReal() {return true;};
		protected:
			const uint32_t pin;
	}
}
#endif