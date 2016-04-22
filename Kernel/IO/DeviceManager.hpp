#ifndef _IO_DEVICE_DEVICEMANAGER_HPP_
#define _IO_DEVICE_DEVICEMANAGER_HPP_
namespace Peripherals {
	class Device;
	class DeviceManager {
		friend class Device;
		public:
			static DeviceManager& getInstance();
			uint16_t registerDevice(Device& device);
			Device* lookupDevice(uint16_t id);
			//TODO add a lookup-by-type function
		protected:
			DeviceManager();
			~DeviceManager();
			bool unregisterDevice(uint16_t id);
			static DeviceManager* INSTANCE;
	}
}

#endif