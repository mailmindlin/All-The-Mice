#include "DeviceManager.hpp"
#include "Device.hpp"
#include <stdlib.h>
#inclide <stdexcept>
#include <limits.h>
namespace Peripherals {
	DeviceManager* DeviceManager::INSTANCE = NULL; 
	DeviceManager& DeviceManager::getInstance() {
		if (!DeviceManager::INSTANCE)
			DeviceManager::INSTANCE = new DeviceManager();
		return DeviceManager::INSTANCE;
	}
	DeviceManager::DeviceManager(size_t initialCapacity) {
		this->registeredDevices = calloc(initialCapacity, sizeof(Device*));
		this->deviceArrayCapacity = initialCapacity;
		this->maxDeviceIdx = 0;
		this->minFreeIdx = 0;
	}
	DeviceManager::~DeviceManager() {
		free(this->registerdDevices);
		this->deviceArrayCapacity = 0;
		this->maxDeviceIdx = 0;
		this->minFreeIdx = 0;
	}
	uint16_t DeviceManager::registerDevice(Device& device) {
		uint16_t id = this->minFreeIdx;
		if (id > this->deviceArrayCapacity) {
			//reallocate array, if possible
			//1.5x
			uint32_t new_cap = this->deviceArrayCapacity + this->deviceArrayCapacity / 2;
			if (new_cap >= USHRT_MAX) {
				if (this->deviceArrayCapacity == USHRT_MAX)
					throw new overflow_error("Ran out of device IDs");
				new_cap = USHRT_MAX;
			}
			Device** tmp = this->registeredDevices;
			this->registeredDevices = realloc(this->registeredDevices, new_cap * sizeof(Device*));
			//Clear array
			for (size_t i = this->deviceArrayCapacity; i < new_cap; i++)
				this->registeredDevices[i] = NULL;
			this->deviceArrayCapacity = new_cap;
			//TODO defragment?
		}
		this->registeredDevices[id] = &device;
		//find the new minFreeIdx
	}
	Device* DeviceManager::lookupDevice(uint16_t id) {
		if (id >= this->maxDeviceIdx)
			return NULL;
		Device* device = this->registeredDevices[id];
		if (device->getId() != id)
			throw new logic_error("Invalid ID");
		return device;
	}
	bool DeviceManager::unregisterDevice(uint16_t id) {
		//Bound check
		if (id >= this->maxDeviceIdx)
			return false;
		
		Device* device = this->registeredDevices[id];
		if (!device)
			return false;
		
		//Set device ID to -1
		device->setId(-1);
		
		//Remove from array
		this->registeredDevices[id] = NULL;
		if (id < this->minFreeIdx)
			this->minFreeIdx = id;
		if (id == this->maxDeviceIdx - 1) {
			//Find the new largest device ID
			for (; this->maxDeviceIdx > 0; this->maxDeviceIdx--)
				if (this->registerdDevices[this->maxDeviceIdx])
					break;
			//The loop found where the last device ID was
			this->maxDeviceIdx++;
		}
		
		return true;
	}
}