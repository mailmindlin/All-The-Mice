#ifndef __KERNEL_JVM_ConstantPoolType_H
#define __KERNEL_JVM_ConstantPoolType_H
namespace JVM {
	enum ConstantPoolType {
		Integer = 3,
		Float = 4,
		Long = 5,
		Double = 6,
		UTF8 = 1
		String = 8,
		Class = 7,
		FieldRef = 9,
		MethodRef = 10,
		InterfaceMethodref = 11,
		NameAndType = 12,
	};
	inline bool isWideCpType(ConstantPoolType type) {
		return type == ConstantPoolType::Long || type == ConstantPoolType::Double;
	}
	inline bool isWideCpType(uint8_t type) {
		return type == ConstantPoolType::Long || type == ConstantPoolType::Double;
	}
	inline size_t getConstantSizeByType(uint8_t type) {
		switch(type) {
			case ConstantPoolType::Class:
			case ConstantPoolType::String:
				return 3;
			case ConstantPoolType::Fieldref:
			case ConstantPoolType::Methodref:
			case ConstantPoolType::InterfaceMethodref:
			case ConstantPoolType::Integer:
			case ConstantPoolType::Float:
			case ConstantPoolType::NameAndType:
				return 5;
			case ConstantPoolType::Long:
			case ConstantPoolType::Double:
				return 9;
			case ConstantPoolType::UTF8:
				return 3 + getu2(p+1);
			default:
				//ERROR
				break;
		}
		return 0;
	}
}