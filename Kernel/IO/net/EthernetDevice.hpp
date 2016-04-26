#ifndef _IO_NET_ETHERNETDEVICE_HPP_
#define _IO_NET_ETHERNETDEVICE_HPP_
#include <Kernel/IO/Device.h>
namespace Peripherals {
	class EthernetDevice : public Device {
		public:
			static EthernetDevice* getDefault();
			static EthernetDevice* getEthernetDevice(uint16_t id);
			static uint16_t registerEthernetDevice(EthernetDevice& device);
			static bool unregisterEthernetDevice(uint16_t id);
			static bool setDefault(uint16_t id);
	}
}
#endif