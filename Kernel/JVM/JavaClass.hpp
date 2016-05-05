#include "JavaClassFile.h"
#include <Kernel/util/String.hpp>
#include "JavaModifierFlags.h"
#include "field/JavaField.hpp"
#include "JavaMethod.hpp"
#include "JavaConstantInfo.hpp"
#include "JavaInterface.hpp"
#include "JavaAttribute.hpp"
namespace JVM {
	class JavaClass {
		public:
			JavaClass(void* data, size_t len);
			virtual ~JavaClass(void);
			const std::string* getName();
			JavaClass* getSuperClass();
			size_t getMethodCount();
			size_t getFieldCount();
			modifiers_t getModifiers();
			JavaConstantInfo* lookupConstant(uint16_t index);
			JavaType* invokeMethod(uint16_t idx, size_t numArgs, )
		protected:
			static bool parseConstantPool(JavaConstantInfo**& pool, void*& data, size_t poolSize);
			static bool parseInterfaces(uint16_t*& interfaces, void*& data, size_t numInterfaces);
			static bool parseFields(JavaField*& fields, void*& data, size_t numFields);
			static bool parseMethods(JavaMethod*& methods, void*& data, size_t numMethods);
			bool parseClass(JavaClass* clazz, void* data, size_t len);
		private:
			bool sanityCheck();
			
			uint16_t majorVersion;
			uint16_t minorVersion;
			uint16_t constantPoolSize;
			JavaContantInfo** constantPool;
			uint16_t modifiers;
			/**
			 * Index in the constant pool representing this class.
			 */
			uint16_t thisClassCpIdx;
			/**
			 * Index in the constant pool representing this's parent class.
			 */
			uint16_t superClassCpIdx;
			uint16_t numInterfaces;
			JavaInterface* interfaces;
			uint16_t numFields;
			JavaField* fields;
			uint16_t numMethods;
			JavaMethod* methods;
			uint16_t numAttributes;
			JavaAttribute* attributes;
	}
}