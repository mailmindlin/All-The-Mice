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
			DeviceManager(size_t initialCapacity =  16);
			~DeviceManager();
			bool unregisterDevice(uint16_t id);
			Device** registeredDevices;
			size_t deviceArrayCapacity;
			size_t maxDeviceIdx;
			size_t minFreeIdx;
			static DeviceManager* INSTANCE;
	}
}

#endif