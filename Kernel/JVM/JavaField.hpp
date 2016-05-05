#include <util/String.hpp>
#include <JVM/Member.hpp>
#include <JVM/Type.hpp>
#include <JVM/JavaAttribute.hpp>
#include "JavaModifierFlags.h"
namespace JVM {
	class JavaClass;
	using namespace std;
	class JavaField : public Member {
		friend class JavaClass;
		public:
			JavaField(field_info& info);
			virtual ~JavaField();
			const Type& getType();
			JavaClass* getDeclaringClass();
		protected:
			modifier_t modifiers;
			uint16_t nameIndex;
			uint16_t descriptorIndex;
			uint16_t numAttributes;
			JavaAttribute* attributes;
	}
}