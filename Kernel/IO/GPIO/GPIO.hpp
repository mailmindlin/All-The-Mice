#ifndef _IO_GPIO_GPIO_HPP
#define _IO_GPIO_GPIO_HPP
#include <Kernel/IO/Memory/memaddr.h>
#include <Kernel/IO/Device.hpp>
namespace Peripherals {
	extern "C++"
	class GPIO : public Device {
		public:
			/**
			 * Get an instance of the GPIO controller.
			 */
			static GPIO& getInstance() {
				if (!GPIO::instance)
					GPIO::instance = new GPIO();
				return GPIO::instance;
			}
			/**
			* A wrapper object for a single GPIO pin. Note that this doesn't have to be a physical pin,
			* and I'm somewhat interested what you could hypothetically do with 'virtual' pins, like
			* mapping another RPi's GPIO to pin numbers on this one, and controlling the other one via
			* an internet protocol, or mapping virtual pins to a simulator software or even OS features.
			*/
			class Pin {
				public:
				Pin(){}
				/**
				 * Read the pin's value as a boolean. If
				 * the pin is set to an output function, calling
				 * this function returns the set value.
				 * @return digital value
				 */
				virtual bool digitalRead();
				/**
				 * Read this pin as an analog value. If this pin
				 * does not support ADC or something, this method
				 * should act as {@link #digitalRead()}, and convert
				 * its output to a double (e.g., true => 3.3V, false => 0V).
				 * @return the voltage of the pin, in volts
				 */
				virtual double analogRead();
				/**
				 * Set the digital value of the pin. If the pin is in a
				 * read mode, this method MUST NOT change the function of
				 * the pin, and do nothing. If this pin is analog, this
				 * method should convert to an analog voltage (e.g., true => 3.3V,
				 * false => 0.0V).
				 */
				virtual bool digitalWrite(bool value);
				/**
				 * Set the analog voltage of the pin. If the pin is in a
				 * read mode, this method MUST NOT change the function of
				 * the pin, and do nothing. If this pin is digital, this
				 * method should convert its analog value to a digital equivalent
				 * (e.g., x > 0V => true, x <= 0V => false).
				 */
				virtual bool analogWrite(double value);
				virtual bool setPUDMode(u8 mode);
				virtual bool pwmWrite(u32 data);
				/**
				 * Whether this pin is real. A real pin is a pin that
				 * is an actual physical hardware device on the local
				 * raspberry pi.
				 */
				virtual bool isReal();
				virtual u32 getNum();
				virtual bool setFunction(u8 function);
				virtual ~Pin(){}
			}
			class GpioPinStore {
				public:
				GpioPinStore(){}
				virtual Pin& getPin(u32 pinNum);
				/**
				 * Whether a pin is currently mapped to the given address.
				 * @param pinNum
				 * @return 
				 */
				virtual bool hasPin(u32 pinNum);
				~GpioPinStore();
			}
			bool addPinStore(GpioPinStore* node);
			class InternalPin;
		protected:
			static GPIO* instance;
			GPIO();
			~GPIO();
			PinMap* map;
			Pin& getPinReal(u32 address);
	}
}

#endif