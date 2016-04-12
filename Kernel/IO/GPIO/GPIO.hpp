#ifndef _IO_GPIO_GPIO_HPP
#define _IO_GPIO_GPIO_HPP
#include "../Memory/memaddr.h"
namespace Peripherals {
	extern "C++"
	class GPIO {
		public:
		class Pin {
			public:
			Pin(){}
			virtual bool digitalRead();
			virtual double analogRead();
			virtual void digitalWrite(bool value);
			virtual void analogWrite(double value);
			virtual bool setPUDMode(u8 mode);
			virtual bool pwmWrite(u32 data);
			virtual bool isReal();
			virtual u32 getNum();
			virtual void setFunction(u8 function);
			virtual ~Pin(){}
		}
		class GpioPinStore {
			public:
			GpioPinStore(){}
			virtual Pin& getPin(u32 pinNum);
			virtual bool hasPin(u32 pinNum);
			~GpioPinStore();
		}
		static &GPIO getInstance();
		bool addPinStore(GpioPinStore* node);
		protected:
		static GPIO instance;
		GPIO();
		~GPIO();
		PinMap* map;
		Pin& getPinReal(u32 address);
	}
}

#endif