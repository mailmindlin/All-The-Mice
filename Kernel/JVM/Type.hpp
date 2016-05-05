#ifndef __KERNEL_JVM_Type_HPP
#define __KERNEL_JVM_Type_HPP
#include <Kernel/util/String.hpp>
namespace JVM {
	class Type {
		virtual ~Type();
		virtual util::String* getTypeName();
	}
}
#endif