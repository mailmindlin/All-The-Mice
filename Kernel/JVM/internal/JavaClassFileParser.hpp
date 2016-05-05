#include "JavaClassFile.h"
namespace JVM {
	class JavaClassFileParser {
		static bool parseConstantPool(cp_info**& pool, void*& data);
		static bool parseInterfaces(uint16_t*& interfaces, void*& data, size_t numInterfaces);
		static bool parseFields(field_info*& fields, void*& data, size_t numFields);
		static bool parseMethods(method_info*& methods, void*& data, size_t numMethods);
		static bool parseClass(JavaClassFile& file, void*& data, size_t len);
	}
}