#include "Charset.hpp"
#include "CharSequence.hpp"
namespace util {
	class String : public CharSequence {
		public:
			String();
			String(u8* bytes, size_t length) : String(bytes, 0, length) {};
			String(u8* bytes, size_t offset, size_t length);
			String(u8* bytes, size_t length, Charset& charset) : String(bytes, 0, length, charset) {};
			String(u8* bytes, size_t offset, size_t length, Charset& charset);
			String(char* value, size_t length);
			String(String& value);
			~String();
			String& concat(String& str);
			bool contains(CharSequence& chars);
			bool contentEquals(CharSequence& chars);
			bool endsWith(String& str);
			bool equalsIgnoreCase(String& other);
			int indexOf(char ch) {return indexOf(ch, 0);}
			int indexOf(char ch, size_t start);
			int indexOf(String& str) {return indexOf(str, 0);}
			int indexOf(String& str, size_t start);
			bool isEmpty() {return this->length() == 0;}
			int lastIndexOf(char ch) {return lastIndexOf(ch, this->length());}
			int lastIndexOf(char ch, size_t end);
			int lastIndexOf(String& str) {return lastIndexOf(str, this->length());}
			int lastIndexOf(String& str, size_t end);
	}
}