namespace util {
	class CharSequence {
		virtual char charAt(size_t index);
		virtual size_t length();
		virtual CharSequence& subSequence(size_t start, size_t end);
	}
}