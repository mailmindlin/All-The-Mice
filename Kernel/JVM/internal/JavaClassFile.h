namespace JVM {
	struct cp_info {
		uint8_t tag;
		uint8_t* info;
	};

	struct field_info {
		uint16_t modifiers;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		attribute_info* attributes;
	};
	
	struct field_info_ref : public field_info {
		field_info* ref;
	};
	
	struct Code_attribute {
		u2 attribute_name_index;
		u4 attribute_length;
		u2 max_stack;
		u2 max_locals;
		u4 code_length;
		u1* code;//[code_length];
		u2 exception_table_length;
		Exception_table* exception_table;//[exception_table_length];
		u2 attributes_count;
		attribute_info* attributes;//[attributes_count];
	};
	struct method_info {
		uint16_t modifiers;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		attribute_info* attributes; //[attributes_count]; 
	};
	
	struct method_info_ref : public method_info {
		method_info* ref;
		Code_attribute* codeRef;
	}

	struct attribute_info{
		uint16_t attribute_name_index;
		uint32_t attribute_length;
		uint8_t* info;//[attribute_length];
	};

	struct JavaClasFile {
		uint32_t magic;
		uint16_t major;
		uint16_t minor;
		uint16_t constantPoolSize;
		cp_info **constantPool; //[constant_pool_count-1]; 
		uint16_t modifiers;
		uint16_t this_class;
		uint16_t super_class;
		uint16_t numInterfaces;
		uint16_t* interfaces; //[interfaces_count]; 
		uint16_t numFields;
		field_info *fields; //[fields_count]; 
		uint16_t numMethods;
		method_info* methods; //[methods_count]; 
		uint16_t numAttributes;
		attribute_info** attributes; //[attributes_count]; 
	};
	struct JavaClasFile_ref {
		uint32_t magic;
		uint16_t major;
		uint16_t minor;
		uint16_t constantPoolSize;
		cp_info **constantPool; //[constant_pool_count-1]; 
		uint16_t modifiers;
		uint16_t this_class;
		uint16_t super_class;
		uint16_t numInterfaces;
		uint16_t* interfaces; //[interfaces_count]; 
		uint16_t numFields;
		field_info_ref *fields; //[fields_count]; 
		uint16_t numMethods;
		method_info_ref* methods; //[methods_count]; 
		uint16_t numAttributes;
		attribute_info_ref** attributes; //[attributes_count]; 
	};
}