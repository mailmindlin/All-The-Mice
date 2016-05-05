#ifndef __KERNEL_JVM_Member_HPP
#define __KERNEL_JVM_Member_HPP
#include <Kernel/util/String.hpp>
#include "Type.hpp"
namespace JVM {
	class Member {
		virtual ~Member();
		virtual util::String* getName();
		virtual modifiers_t getModifiers();
	}
}
#endif