#ifndef __KERNEL_JVM_JavaMethod_HPP
#define __KERNEL_JVM_JavaMethod_HPP

#include "Member.hpp"
#include "JavaClass.hpp"
namespace JVM {
	/**
	 * Struct to encapsulate how the method is stored in the file.
	 */
	struct JavaMethodInfo {
		uint16_t modifiers;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		attribute_info* attributes; //[attributes_count]; 
	}
	class JavaMethod : public Member {
		JavaMethod(method_info& info);
		JavaClass* getClass();
		size_t getParameterCount();
		JavaClass* getParameterType(size_t idx);
	}
}
#endif