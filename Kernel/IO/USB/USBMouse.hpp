#ifndef _IO_USB_USBMOUSE_HPP
#define _IO_USB_USBMOUSE_HPP
#include <Kernel/IO/Device.h>

namespace Peripherals {
namespace USB {
	class USBMouse;
	typedef void USBMouseHandler (USBMouse* device, unsigned buttons, int8_t dx, int8_t dy);
	class USBMouse : public Device {
			void setHandler(USBMouseHandler* handler);
			
		protected:
			USBMouseHandler* handler;
	}
}
}


#endif