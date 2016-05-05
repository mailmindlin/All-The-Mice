#include "JavaClassFile.h"
#include <string>
namespace JVM {
	using namespace std;
	class JavaClassloader {
		public:
			JavaClassLoader();
			virtual ~JavaClassLoader();
			JavaClass* findClass(string& name);
			JavaClass* findLoadedClass(string& name);
			JavaClass* loadClass(string& name);
			JavaClasspath* getClasspath();
		protected:
	}
}