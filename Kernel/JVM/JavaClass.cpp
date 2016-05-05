#include "JavaClass.hpp"
namespace JVM {
	static inline uint32_t get4(void*& p) {
		uint32_t result = *(reinterpret_cast<uint32_t*>(p));
		p += 4;
		return result;
	}
	static inline uint16_t get2(void*& p) {
		uint16_t result = *(reinterpret_cast<uint16_t*>(p));
		p += 2;
		return result;
	}
	JavaClass::JavaClass(void* data, size_t len) {
		this->parseClass(data, len);
	}
	bool JavaClass::sanityCheck() {
		JavaConstantInfo* thisCp = this->lookupConstant(this->thisClassCpIdx);
		if (thisCp == NULL || thisCp->tag != ConstantPoolType::Class)
			return false;
		JavaConstantInfo* superCp = this->lookupConstant(this->superClassCpIdx);
		if (superCp == NULL || superCp->tag != ConstantPoolType::Class)
			return false;
	}
	JavaClass::~JavaClass() {
		if (this->constantPoolSize > 0 || this->constantPool != NULL)
			delete this->constantPool;
		if (this->numInterfaces > 0 || this->interfaces != NULL)
			delete this->interfaces;
		if (this->numFields > 0 || this->fields != NULL)
			delete this->fields;
		//TODO finish
	}
}