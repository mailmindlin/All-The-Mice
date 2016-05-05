namespace JVM {
	enum JavaModifierFlag {
		/*Declared public; may be accessed from outside its package.  */
		PUBLIC  = 0x0001,
		/*Declared protected; may be accessed within subclasses.  */
		PRIVATE = 0x0002,
		/*Declared private; accessible only within the defining class.  */
		PROTECTED = 0x0004,
		/*Declared static.*/
		STATIC = 0x0008,
		/*Declared final; may not be verridden.  */
		FINAL = 0x0010,
		/*Declared synchronized; invocation is wrapped in a monitor lock.  */
		SYNCHRONIZED = 0x0020,
		/*Declared native; implemented in a language other than Java.  */
		NATIVE = 0x0100,
		/*Declared abstract; no implementation is provided.  */
		ABSTRACT = 0x0400,
		/*Declared strictfp; floating-point mode is FP-strict  */
		STRICT = 0x0800
	}
	typedef uint16_t modifiers_t;
}